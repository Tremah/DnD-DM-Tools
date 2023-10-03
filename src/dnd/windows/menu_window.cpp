#include "menu_window.h"

#include <iostream>
#include <string>

#include <imgui/imgui.h>
#include <nlohmann/json.hpp>

#include <dnd/dm_tool_app.h>

namespace Dnd
{
  void MenuWindow::init()
  {
    characterEditorWindow_ = new CharacterEditorWindow{};
    characterEditorWindow_->init();
    DmToolApp::get()->addWindow(characterEditorWindow_);
  }

  void MenuWindow::update()
  {
    if(visible_)
    {
      if(!ImGui::Begin("Menu", &visible_, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
      {
        ImGui::End();
      }
      else
      {
        ImGui::Dummy(ImVec2{0, 15});
        ImGui::Dummy(ImVec2{10, 0});
        ImGui::SameLine();

        ImVec2 buttonSpacingX{0, 0};
        ImVec2 standardSize{ImGui::GetFontSize() * 6, 80};

        ImGui::Button("Start Game Session", ImVec2{ImGui::GetFontSize() * 8, 80});
        ImGui::SameLine();

        ImGui::Dummy(buttonSpacingX);
        ImGui::SameLine();

        std::string buttonName = "Open Combat Window";
        ImGui::Button(buttonName.c_str(), ImVec2{ImGui::GetFontSize() * 9, 80});
        ImGui::SameLine();

        ImGui::Dummy(buttonSpacingX);
        ImGui::SameLine();

        buttonName = "Open Character Editor";
        if(characterEditorWindow_->isVisible())
        {
          buttonName = "Close Character Editor";
        }
        if(ImGui::Button(buttonName.c_str(), ImVec2{ImGui::GetFontSize() * 9, 80}))
        {
          if(characterEditorWindow_)
          {
            characterEditorWindow_->setVisibility(!characterEditorWindow_->isVisible());
          }
        }
        ImGui::SameLine();

        ImGui::Dummy(buttonSpacingX);
        ImGui::SameLine();
        ImGui::Button("Open Session Log", ImVec2{ImGui::GetFontSize() * 8, 80});
        ImGui::SameLine();

        ImGui::Dummy(buttonSpacingX);
        ImGui::SameLine();
        if(ImGui::Button("Close Application", ImVec2{ImGui::GetFontSize() * 8, 80}))
        {
          isAppRunning_ = false;
        }
        ImGui::End();
      }
    }

  }

  void MenuWindow::shutdown()
  {

  }

} // Dnd