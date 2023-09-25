//
// Created by micro on 24/09/2023.
//

#ifndef DND_DM_TOOLS_DM_TOOL_IMGUI_UI_ELEMENTS_HPP
#define DND_DM_TOOLS_DM_TOOL_IMGUI_UI_ELEMENTS_HPP

#include <string>
#include <string_view>

#include <imgui/imgui.h>
#include <dnd/utility.h>


namespace Dnd
{
  void makePartyWindow()
  {
    auto values = parseCsvToMap("assets/csv_import/character_overview.csv");

    std::string windowName{"Party Overview"};
    if(ImGui::Begin(windowName.c_str()))
    {
      for(std::size_t characterIndex = 0; characterIndex < values.numRows_; ++characterIndex)
      {
        if (ImGui::CollapsingHeader(values.csvValuesPerColumn_.at("Name").at(characterIndex).c_str()))
        {
          ImGui::Dummy(ImVec2(0.0f, 1.0f));
          auto tableStyleFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_PadOuterX;
          if (ImGui::BeginTable("table", 2, tableStyleFlags))
          {
            //One table row for each property
            //Table is transposed on input, because of the vizualization within the app
            for (std::size_t propertyRowIndex = 0; propertyRowIndex < values.numColumns_; ++propertyRowIndex)
            {
              ImGui::TableNextRow();
              ImGui::TableNextColumn();
              const std::string& columnName = values.columnNames_.at(propertyRowIndex);
              ImGui::Text("%s", columnName.c_str());
              ImGui::TableNextColumn();
              ImGui::Text("%s",  values.csvValuesPerColumn_.at(columnName).at(characterIndex).c_str());
            }
            ImGui::EndTable();
            ImGui::Dummy(ImVec2(0.0f, 1.0f));
          }
          /*ImGui::Text("Class: %s", values.csvValuesPerColumn_.at("Class").at(i).c_str());
          ImGui::Text("Race: %s", values.csvValuesPerColumn_.at("Race").at(i).c_str());
          ImGui::Text("Background: %s", values.csvValuesPerColumn_.at("Background").at(i).c_str());
          ImGui::Text("Proficiency Bonus: %s", values.csvValuesPerColumn_.at("Proficiency Bonus").at(i).c_str());
          ImGui::Text("Strength Modifier: %s", values.csvValuesPerColumn_.at("Strength Modifier").at(i).c_str());
          ImGui::Text("Dexterity Modifier: %s", values.csvValuesPerColumn_.at("Dexterity Modifier").at(i).c_str());
          ImGui::Text("Constitution Modifier: %s", values.csvValuesPerColumn_.at("Constitution Modifier").at(i).c_str());
          ImGui::Text("Intelligence Modifier: %s", values.csvValuesPerColumn_.at("Intelligence Modifier").at(i).c_str());
          ImGui::Text("Wisdom Modifier: %s", values.csvValuesPerColumn_.at("Wisdom Modifier").at(i).c_str());
          ImGui::Text("Charisma Modifier: %s", values.csvValuesPerColumn_.at("Charisma Modifier").at(i).c_str());*/
        }
      }
    }
    ImGui::End();
  }
}

#endif //DND_DM_TOOLS_DM_TOOL_IMGUI_UI_ELEMENTS_HPP
