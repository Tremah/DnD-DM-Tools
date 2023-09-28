#include "party_overview_window.h"

#include <string>
#include <cstdint>

#include <imgui/imgui.h>

namespace Dnd
{
  void PartyOverviewWindow::init()
  {
    characterProperties_ = parseCsvToMap("assets/csv_import/character_overview.csv");
  }

  void PartyOverviewWindow::update()
  {
    std::string windowName{"Party Overview"};
    if(ImGui::Begin(windowName.c_str()))
    {
      for(std::size_t characterIndex = 0; characterIndex < characterProperties_.numRows_; ++characterIndex)
      {
        if (ImGui::CollapsingHeader(characterProperties_.csvValuesPerColumn_.at("Name").at(characterIndex).c_str()))
        {
          ImGui::Dummy(ImVec2(0.0f, 1.0f));
          auto tableStyleFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_PadOuterX;
          if (ImGui::BeginTable("table", 2, tableStyleFlags))
          {
            //One table row for each property
            //Table is transposed on input, because of the vizualization within the app
            for (std::size_t propertyRowIndex = 0; propertyRowIndex < characterProperties_.numColumns_; ++propertyRowIndex)
            {
              ImGui::TableNextRow();
              ImGui::TableNextColumn();
              const std::string& columnName = characterProperties_.columnNames_.at(propertyRowIndex);
              ImGui::Text("%s", columnName.c_str());
              ImGui::TableNextColumn();
              ImGui::Text("%s",  characterProperties_.csvValuesPerColumn_.at(columnName).at(characterIndex).c_str());
            }
            ImGui::EndTable();
            ImGui::Dummy(ImVec2(0.0f, 1.0f));
          }
        }
      }
    }
    ImGui::End();
  }

  void PartyOverviewWindow::shutdown()
  {

  }
} // Dnd