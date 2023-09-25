//
// Created by micro on 24/09/2023.
//
#include "dm_tool_app.h"

#include <dnd/utility.h>

namespace Dnd
{
  void DmToolApp::init()
  {
    initOpenGLComponentsForDraw();
    addTexture("MAIN_WINDOW_BACKGROUND", loadTextureFromFile("assets/textures/main_window_background.jpg"));
  }

  void DmToolApp::addValue(const std::string& key, const std::string& value)
  {

  }

  void DmToolApp::addTexture(const std::string& name, Dnd::Texture texture)
  {
    textures_.insert({name, texture});
  }

  const Texture& DmToolApp::getTextureByName(const std::string& name) const
  {
    return textures_.at(name);
  }

  void DmToolApp::drawBackgroundImage()
  {
    std::vector<float> vertices_
      {
        -1.f, -1.f, 0.f, 0.f,
        1.f, -1.f, 1.f, 0.f,
        1.f,  1.f, 1.f, 1.f,
        -1.f, -1.f, 0.f, 0.f,
        1.f,  1.f, 1.f, 1.f,
        -1.f,  1.f, 0.f, 1.f
      };

    GLuint numberOfVertices = 6;
    GLuint componentsPerVertex = 4;

    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * componentsPerVertex * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
}
