#pragma once
#ifndef DND_UTILITY_H
#define DND_UTILITY_H

#include <string>

#include <glad/gl.h>

#include "dnd/data/types.h"

namespace Dnd
{
  Texture loadTextureFromFile(const std::string& filePath);

  void initOpenGLComponentsForDraw();

  void setOpenGLDebugCallback();

  std::unordered_map<GLenum, std::string> separateShaders(const std::string& shaderSource);

  std::string readFromFile(const std::string& filePath);

/**
  *  \brief  Transforms a csv file into a struct, containing the values and metadata.
  *
  *  Returns a CsvValues object, containing an unordered map for value access via
  *  the column names within the csv file. It also contains metadata about the imported
  *  data.
  *
  *  @note
  *  This function cannot be used to import any kind of csv file. It only exist to
  *  read data into the app while development is ongoing.
  *
  *  @param filePath Path to the csv file including its name.
  *
  *  \return CsvValues object.
  */
  CsvValues parseCsvToMap(const std::string& filePath);

  template <typename EnumType>
  constexpr auto enumToIntegral(EnumType enumeration) -> std::underlying_type_t<EnumType>
  {
    return static_cast<std::underlying_type_t<EnumType>>(enumeration);
  }

  template <typename EnumType, typename ValueType>
  constexpr auto integralToEnum(ValueType item) -> EnumType
  {
    return static_cast<EnumType>(item);
  }
}

#endif //DND_UTILITY_H
