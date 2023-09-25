//
// Created by micro on 24/09/2023.
//

#ifndef DND_DM_TOOLS_TYPES_H
#define DND_DM_TOOLS_TYPES_H

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include <glad/gl.h>

namespace Dnd
{

  using CsvValueMapType = std::unordered_map<std::string, std::vector<std::string>>;

  struct Texture
  {
  public:
    Texture() = default;

    std::string name_{};
    GLuint textureId_ = -1;
    int width_ = 0;
    int height_ = 0;
  };

  struct OpenGLData
  {
  public:
    OpenGLData() = default;

    GLuint vertexArrayId_ = -1;
    GLuint vertexBufferId_ = -1;

    GLuint shaderId_ = -1;
    std::string shaderName_{};
  };

  struct CsvValues
  {
    CsvValues() = default;

    //Access values via the column name and row within the csv table
    CsvValueMapType csvValuesPerColumn_{};
    std::vector<std::string> columnNames_{};

    uint16_t numColumns_ = 0;
    uint16_t numRows_ = 0;
  };
}

#endif //DND_DM_TOOLS_TYPES_H
