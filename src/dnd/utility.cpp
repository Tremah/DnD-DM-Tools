#include "utility.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <regex>
#include <array>

#define STB_IMAGE_IMPLEMENTATION
#include <dnd/stb_image.h>


namespace Dnd
{
  Texture loadTextureFromFile(const std::string& filePath)
  {
    Texture texture{};
    stbi_set_flip_vertically_on_load(1);

    //load texture
    int channels = 0;
    unsigned char *textureBuffer = stbi_load(filePath.c_str(), &texture.width_, &texture.height_, &channels, 4);
    if (textureBuffer == nullptr)
    {
      return Texture{};
    }

    int internalFormat = 0;
    int dataFormat = 0;
    internalFormat = GL_RGBA8;
    dataFormat = GL_RGBA;

    GLuint textureId = 0;

    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
    texture.textureId_ = textureId;
    //add padding to the created texture's size
    glTextureStorage2D(texture.textureId_, 1, internalFormat, texture.width_, texture.height_);
    //GL_NEAREST = more pixelated
    //GL_LINEAR =  weighted average of the four surrounding pixels
    glTextureParameteri(texture.textureId_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(texture.textureId_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(texture.textureId_, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture.textureId_, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(texture.textureId_, 0, 0, 0, texture.width_, texture.height_, dataFormat, GL_UNSIGNED_BYTE, textureBuffer);

    stbi_image_free(textureBuffer);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
  }

  void initOpenGLComponentsForDraw()
  {
    setOpenGLDebugCallback();

    //Init OpenGL components
    OpenGLData openGLData{};
    GLuint vertexArrayId;
    GLuint vertexBufferId;

    glGenVertexArrays(1, &vertexArrayId);
    glGenBuffers(1, &vertexBufferId);

    glBindVertexArray(vertexArrayId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

    GLuint numberOfVertices = 6;
    GLuint componentsPerVertex = 4;

    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * componentsPerVertex * sizeof(float), nullptr, GL_STATIC_DRAW);

    uint32_t attributeId = 0;
    glVertexAttribPointer(attributeId, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(attributeId);
    glVertexAttribPointer(++attributeId, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(attributeId);

    //Load, compile, and link vertex and fragment shaders
    auto shaderSources = separateShaders(readFromFile("assets/shaders/background_shader.glsl"));
    std::array<GLenum, 2> shaderIds{};
    std::size_t shaderIdCount = 0;
    auto program = glCreateProgram();

    for (const auto& [type, source] : shaderSources)
    {
      //createBuffers and compile shader
      uint32_t shader = glCreateShader(type);
      const char* shaderCode = source.c_str();
      glShaderSource(shader, 1, &shaderCode, nullptr);
      glCompileShader(shader);
      GLint compiled = 0;
      //check shader compilation status
      glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
      if (!compiled)
      {
        //if compile error, delete shader
        GLint maxLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLen);
        std::vector<GLchar> infoLog(maxLen);
        glGetShaderInfoLog(shader, maxLen, &maxLen, &infoLog[0]);
        glDeleteShader(shader);

        std::cout << "Error compiling shader:\n";
        std::cout << infoLog.data() << std::endl;
      }
      glAttachShader(program, shader);
      shaderIds[shaderIdCount++] = shader;
    }

    //link program
    glLinkProgram(program);
    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
      //if linking error reverse everything
      GLint maxLen = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLen);
      std::vector<GLchar> infoLog(maxLen);
      glGetProgramInfoLog(program, maxLen, &maxLen, &infoLog[0]);

      for (auto i : shaderIds)
      {
        glDeleteShader(i);
      }
      glDeleteProgram(program);

      std::cout << "Error linking shader:\n";
      std::cout << infoLog.data() << std::endl;
    }
    else
    {
      glUseProgram(program);
      glUniform1i(glGetUniformLocation(program, "textureSampler"), 0);

      //already linked shaders can be deleted
      for (auto i : shaderIds)
      {
        glDetachShader(program, i);
        glDeleteShader(i);
      }
    }

    //Save OpenGL values
    openGLData.vertexArrayId_ = vertexArrayId;
    openGLData.vertexBufferId_ = vertexBufferId;
    openGLData.shaderId_ = program;
    openGLData.shaderName_ = "BACKGROUND_SHADER";
  }

  void setOpenGLDebugCallback()
  { //OpenGL Debug message callback
    glDebugMessageCallback(
      [](GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message,
         const void* userParam)
      {
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
        std::cout << "Debug message(" << id << "):" << message << "\n";

        switch (source)
        {
          case GL_DEBUG_SOURCE_API:
            std::cout << "Source: API";
            break;
          case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "Source: Window System";
            break;
          case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "Source: Shader Compiler";
            break;
          case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "Source: Third Party";
            break;
          case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "Source: Application";
            break;
          case GL_DEBUG_SOURCE_OTHER:
            std::cout << "Source: Other";
            break;
        }
        std::cout << "\n";

        switch (type)
        {
          case GL_DEBUG_TYPE_ERROR:
            std::cout << "Type: Error";
            break;
          case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Type: Deprecated Behavior";
            break;
          case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Type: Undefined Behavior";
            break;
          case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Type: Portability";
            break;
          case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Type: Performance";
            break;
          case GL_DEBUG_TYPE_MARKER:
            std::cout << "Type: Marker";
            break;
          case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Type: Push Group";
            break;
          case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Type: Pop Group";
            break;
          case GL_DEBUG_TYPE_OTHER:
            std::cout << "Type: Other";
            break;
        }
        std::cout << "\n";

        switch (severity)
        {
          case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "Severity: high";
            break;
          case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Severity: medium";
            break;
          case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Severity: low";
            break;
          case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Severity: notification";
            break;
        }
        std::cout << "\n";
        std::cout << "---------------";
        std::cout << "\n";
      }, nullptr);
  }

  std::unordered_map<GLenum, std::string> separateShaders(const std::string& shaderSource)
  {
    std::string typeToken = "#type";
    std::size_t typeTokenLen = typeToken.length();
    std::size_t offset = 0;
    std::size_t typePos = shaderSource.find(typeToken, offset);
    //LU_ASSERT(typePos != std::string::npos, "Syntax error in shader file: No shaders defined!")

    std::unordered_map<GLenum, std::string> shaders;
    while (typePos != std::string::npos)
    {
      //find end of line for shader type statement
      std::size_t eol = shaderSource.find_first_of("\r\n", typePos);
      //determine shader type
      std::size_t nameStart = shaderSource.find_first_not_of(' ', typePos + typeTokenLen);
      std::size_t nameEnd = shaderSource.find_last_not_of(' ', eol - 1);
      std::string shaderType = shaderSource.substr(nameStart, nameEnd - nameStart + 1);
      //find start of shader code
      std::size_t shaderStart = shaderSource.find_first_not_of("\r\n", eol); /*start position for shader source code*/
      //find start of the next shader
      std::size_t nextShaderPos = ((shaderSource.find(typeToken, shaderStart) != std::string::npos)
                                   ? shaderSource.find(typeToken, shaderStart) : shaderSource.length()) - 1;
      //find the end of the current shader code
      std::size_t shaderEnd = shaderSource.find_last_not_of("\r\n", nextShaderPos) - shaderStart + 1;

      int shaderTypeOpenGL = 0;
      if (shaderType == "vertex")
      {
        shaderTypeOpenGL =  GL_VERTEX_SHADER;
      }
      if (shaderType == "fragment")
      {
        shaderTypeOpenGL =  GL_FRAGMENT_SHADER;
      }

      shaders.insert({shaderTypeOpenGL, shaderSource.substr(shaderStart, shaderEnd)});

      offset += shaderEnd;
      typePos = shaderSource.find(typeToken, offset);
    }

    return shaders;
  }

  std::string readFromFile(const std::string& filePath)
  {
    std::ifstream inFile{filePath, std::ios::in | std::ios::binary};
    //LU_ASSERT(inFile, "File " + filePath + " could not be opened!")
    std::string fileContent;
    if (inFile)
    {
      inFile.seekg(0, std::ios::end);
      size_t size = inFile.tellg();
      fileContent.resize(size);
      inFile.seekg(0, std::ios::beg);
      inFile.read(&fileContent[0], size);

      //normalize line ending
      fileContent = std::regex_replace(fileContent, std::regex{"\r\n"}, "\n");
      //remove trailing new lines
      auto lastNonNewLine = fileContent.find_last_not_of("\n");
      if (lastNonNewLine < fileContent.size() - 1)
      {
        fileContent = fileContent.substr(0, lastNonNewLine + 1);
      }
    }

    return fileContent;
  }


  CsvValues parseCsvToMap(const std::string& filePath)
  {
    std::string fileContent = readFromFile(filePath);
    std::string separator{";"};

    std::size_t lineCount = 0;
    std::size_t contentRowCount = 0;
    std::size_t contentColumnCount = 0;
    std::size_t valueRowCount = 0;

    std::vector<std::string> csvColumns{};
    csvColumns.reserve(10);

    std::vector<std::vector<std::string>> csvRows{};
    csvRows.reserve(10);

    while(true)
    {
      //Find position of first newline and split string there
      auto nextNewLinePos = fileContent.find_first_of("\n");
      std::string line = fileContent.substr(0, nextNewLinePos);

      //Cut extracted part from file content
      ++lineCount;

      //Te first 2 lines ar unimportant
      if (lineCount == 3)
      {
        //Column names
        auto nextSeparatorPos = line.find_first_of(separator);
        std::string valueList = line;
        while (true)
        {
          nextSeparatorPos = valueList.find_first_of(separator);
          std::string column = valueList.substr(0, nextSeparatorPos);
          csvColumns.push_back(column);
          ++contentColumnCount;

          if (nextSeparatorPos == valueList.npos)
          {
            break;
          }
          valueList = valueList.substr(nextSeparatorPos + 1);
        }
      }

      if (lineCount > 3)
      {
        auto nextSeparatorPos = line.find_first_of(separator);
        //One vector for each column
        csvRows.push_back(std::vector<std::string>{});
        std::string valueList = line;
        while (true)
        {
          nextSeparatorPos = valueList.find_first_of(separator);
          std::string value = valueList.substr(0, nextSeparatorPos);
          csvRows.at(csvRows.size() - 1).push_back(value);

          if (nextSeparatorPos == valueList.npos)
          {
            break;
          }
          valueList = valueList.substr(nextSeparatorPos + 1);
        }
        ++contentRowCount;
      }

      //Check if the last line was processed
      if(nextNewLinePos == fileContent.npos && line == fileContent)
      {
        break;
      }
      fileContent = fileContent.substr(++nextNewLinePos);
    }

    //Create the unordered map containing a vector per csv column name
    CsvValues csvValues{};
    for(const auto& column : csvColumns)
    {
      csvValues.csvValuesPerColumn_.insert({column, std::vector<std::string>{}});
    }

    for(auto& row : csvRows)
    {
      for(std::size_t i = 0; i < row.size(); ++i)
      {
        const auto& column = csvColumns.at(i);
        csvValues.csvValuesPerColumn_.at(column).push_back(row.at(i));
      }
    }
    csvValues.columnNames_ = csvColumns;
    csvValues.numColumns_ = contentColumnCount;
    csvValues.numRows_ = contentRowCount;

    return csvValues;
  }
}
