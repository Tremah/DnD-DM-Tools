#include "dm_tool_app.h"

#include <dnd/windows/dice_roll_window.h>
#include <dnd/windows/party_overview_window.h>
#include <dnd/windows/menu_window.h>
#include <dnd/windows/log_window.h>

#include <dnd/utility.h>


namespace Dnd
{
  void DmToolApp::init()
  {
    initOpenGLComponentsForDraw();
    addTexture("MAIN_WINDOW_BACKGROUND", loadTextureFromFile("assets/textures/main_window_background.jpg"));
    addTexture("MENU_ICON_START_SESSION", loadTextureFromFile("assets/textures/d20.png"));

    windowList_.reserve(10);
    windowList_.emplace_back(new Dnd::DiceRollWindow{});
    windowList_.emplace_back(new Dnd::PartyOverviewWindow{});
    windowList_.emplace_back(new Dnd::MenuWindow{running_});

    logWindow_ = new Dnd::LogWindow{};
    windowList_.emplace_back(logWindow_);

    logEntries_.reserve(1000);

    instance_ = this;
    running_ = true;

    for(auto window : windowList_)
    {
      window->init();
    }
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

    auto backgroundTexture = textures_.at("MAIN_WINDOW_BACKGROUND");
    glBindTextureUnit(0, backgroundTexture.textureId_);

    glBufferData(GL_ARRAY_BUFFER, numberOfVertices * componentsPerVertex * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  DmToolApp* DmToolApp::get()
  {
    return instance_;
  }

  void DmToolApp::addWindow(Window* window)
  {
    windowList_.emplace_back(window);
  }

  void DmToolApp::update()
  {
    drawBackgroundImage();
    for(auto window : windowList_)
    {
      if (!window->isVisible())
      {
        continue;
      }
      window->update();
    }
  }

  void DmToolApp::shutdown()
  {
    for(auto window : windowList_)
    {
      window->shutdown();
      delete window;
    }
  }

  bool DmToolApp::isRunning() const
  {
    return running_;
  }

  void DmToolApp::setRunning(const bool running)
  {
    running_ = running;
  }

  void DmToolApp::clearLog()
  {
    logEntries_.clear();
  }

  const std::vector<std::string>& DmToolApp::getLog() const
  {
    return logEntries_;
  }

  LogWindow* DmToolApp::getLogWindow()
  {
    return logWindow_;
  }
}
