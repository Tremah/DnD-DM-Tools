#include "menu_window.h"

#include <imgui/imgui.h>

#include <dnd/dm_tool_app.h>

namespace Dnd
{
  void MenuWindow::init()
  {

  }

  void MenuWindow::update()
  {
    if(open_)
    {
      if(!ImGui::Begin("Menu", &open_, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
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
        ImGui::Button("Start Combat", standardSize);
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