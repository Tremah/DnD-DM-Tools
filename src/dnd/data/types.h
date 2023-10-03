#pragma once
#ifndef DND_DM_TOOLS_TYPES_H
#define DND_DM_TOOLS_TYPES_H

#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace Dnd
{
  //Types used by the application

  //Aliases
  using CsvValueMapType = std::unordered_map<std::string, std::vector<std::string>>;

  //Application related types
  struct Texture
  {
  public:
    Texture() = default;

    std::string name_{};
    int textureId_ = -1;
    int width_ = 0;
    int height_ = 0;
  };

  struct OpenGLData
  {
  public:
    OpenGLData() = default;

    int vertexArrayId_ = -1;
    int vertexBufferId_ = -1;

    int shaderId_ = -1;
    std::string shaderName_{};
  };

  //Misc
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
