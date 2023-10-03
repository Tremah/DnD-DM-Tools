#include "character_editor_window.h"

#include <fstream>
#include <algorithm>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <nlohmann/json.hpp>

#include <dnd/data/dnd_data.h>
#include <dnd/utility.h>
#include <dnd/imgui_config.h>

namespace Dnd
{
  void CharacterEditorWindow::init()
  {
    //Only show when opened via menu
    setVisibility(false);
  }

  void CharacterEditorWindow::update()
  {
    ImGui::SetNextWindowSize(ImVec2(2300, 1300), ImGuiCond_Once);
    auto windowBgColor = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{windowBgColor.x, windowBgColor.y, windowBgColor.z, 0.99f});
    if(!ImGui::Begin("Character Editor", &visible_))
    {
      ImGui::End();
    }
    else
    {
      auto tableStyleFlags = ImGuiTableFlags_PadOuterX;
      auto columnStyleFlags = ImGuiTableColumnFlags_WidthFixed;
      auto comboBoxStyleFlags = ImGuiComboFlags_PopupAlignLeft;

      auto sameLineFirstColumn = 150.f;
      auto sameLineSecondColumn = 120.f;
      if (ImGui::BeginTable("##character_editor_layout_table", 5, tableStyleFlags))
      {
        ImGui::TableSetupColumn("", columnStyleFlags, 450.f);
        ImGui::TableSetupColumn("", columnStyleFlags, 320.f);

        //Larger font for the table headers
        ImGui::PushFont(ImGuiConfig::imGuiFonts_.at("Lato").at(ImGuiConfig::standardFontSize_ + 4));
        // First Row (Section header)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
            ImGui::Text("General");
          ImGui::TableNextColumn();
            ImGui::Text("Abilities");
        ImGui::PopFont();

        //Second Row (Input UI)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
            ImGui::Text("Character Name: ");
            ImGui::SameLine(sameLineFirstColumn);
            ImGui::PushItemWidth(250.f);
            ImGui::InputText("##char_edit_name", &character_.name_);
            ImGui::PopItemWidth();
          ImGui::TableNextColumn();
            buildAbilityScoreUiItem("Strength", sameLineSecondColumn);

        //Third Row (Input UI)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::Text("Age: ");
          ImGui::SameLine(sameLineFirstColumn);
          ImGui::PushItemWidth(100.f);
          ImGui::InputInt("##char_edit_age", &character_.age_);
          character_.age_ = std::max(0, character_.age_);
          ImGui::PopItemWidth();
        ImGui::TableNextColumn();
          buildAbilityScoreUiItem("Dexterity", sameLineSecondColumn);

        //Forth Row (Input UI)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
            ImGui::Text("Level");
            ImGui::SameLine(sameLineFirstColumn);
            ImGui::PushItemWidth(100.f);
            ImGui::InputInt("##char_edit_level", &character_.level_);
            character_.level_ = std::max(1, character_.level_);
            ImGui::PopItemWidth();
          ImGui::TableNextColumn();
            buildAbilityScoreUiItem("Constitution", sameLineSecondColumn);

        //Forth Row (Input UI)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
            ImGui::Text("XP");
            ImGui::SameLine(sameLineFirstColumn);
            ImGui::PushItemWidth(175.f);
            ImGui::InputInt("##char_edit_xp", &character_.xp_);
            character_.xp_ = std::max(0, character_.xp_);
            ImGui::PopItemWidth();
          ImGui::TableNextColumn();
            buildAbilityScoreUiItem("Intelligence", sameLineSecondColumn);

        //Fifth Row (Input UI)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::Text("HP");
          ImGui::SameLine(sameLineFirstColumn);
          ImGui::PushItemWidth(175.f);
          ImGui::InputInt("##char_edit_hp", &character_.hp_);
          character_.xp_ = std::max(0, character_.hp_);
          ImGui::PopItemWidth();
          ImGui::TableNextColumn();
            buildAbilityScoreUiItem("Wisdom", sameLineSecondColumn);

        //Sixth Row (Input UI)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
            ImGui::Text("Race");
            ImGui::SameLine(sameLineFirstColumn);

            auto& raceStringValues = DndData::race_.races_;
            ImGui::PushItemWidth(250.f);
            if (ImGui::BeginCombo("##char_edit_race", character_.race_.c_str(), comboBoxStyleFlags))
            {
              for(std::size_t i = 0; i < raceStringValues.size(); ++i)
              {
                if (ImGui::Selectable(raceStringValues.at(i).c_str(), false))
                {
                  character_.race_ = raceStringValues.at(i);
                }
              }
              ImGui::EndCombo();
            }
            ImGui::PopItemWidth();
          ImGui::TableNextColumn();
            buildAbilityScoreUiItem("Charisma", sameLineSecondColumn);

        //Seventh Row (Input UI)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
            ImGui::Text("Class");
            ImGui::SameLine(sameLineFirstColumn);

            auto& classStringValues = DndData::class_.classes_;
            ImGui::PushItemWidth(250.f);
            if (ImGui::BeginCombo("##char_edit_class", character_.class_.c_str(), comboBoxStyleFlags))
            {
              for(std::size_t i = 0; i < classStringValues.size(); ++i)
              {
                if (ImGui::Selectable(classStringValues.at(i).c_str(), false))
                {
                  character_.class_ = classStringValues.at(i);
                }
              }
              ImGui::EndCombo();
            }
            ImGui::PopItemWidth();

        //Eigth Row (Input UI)
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::Text("Alignment");
          ImGui::SameLine(sameLineFirstColumn);

          auto& alignmentStringValues = DndData::alignment_.alignments_;
          ImGui::PushItemWidth(250.f);
          if (ImGui::BeginCombo("##char_edit_alignment", character_.alignment_.c_str(), comboBoxStyleFlags))
          {
            for(std::size_t i = 0; i < alignmentStringValues.size(); ++i)
            {
              if (ImGui::Selectable(alignmentStringValues.at(i).first.c_str(), false))
              {
                character_.alignment_ = alignmentStringValues.at(i).first;
              }
            }
            ImGui::EndCombo();
          }
          ImGui::PopItemWidth();

        //Eighth Row
        ImGui::TableNextRow();
          ImGui::TableNextColumn();
            ImGui::Text("Proficiency Bonus");
            ImGui::SameLine(sameLineFirstColumn);
            ImGui::PushItemWidth(100.f);
            ImGui::InputInt("##char_edit_proficiency_bonus", &character_.proficiencyBonus_);
            character_.proficiencyBonus_ = std::max(0, character_.proficiencyBonus_);
            ImGui::PopItemWidth();
        ImGui::EndTable();
      }
      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  void CharacterEditorWindow::shutdown()
  {

  }

  void CharacterEditorWindow::save()
  {
    //Prepare output file
    std::ofstream sessionFile;

    std::string outputFile = "data/";
    //Replace whitespace in character name for filename
    std::string characterNameNoWhitespace{};
    if(!character_.name_.empty())
    {
      characterNameNoWhitespace = character_.name_;
    }
    else
    {
      characterNameNoWhitespace = "no_name";
    }
    std::ranges::replace(characterNameNoWhitespace, ' ', '_');
    outputFile += characterNameNoWhitespace + "_character_sheet" +  ".json";

    sessionFile.open(outputFile, std::ofstream::trunc);
    if(sessionFile.is_open())
    {
      nlohmann::json json = character_;
      std::string jsonString = json.dump();

      sessionFile << jsonString;
      sessionFile.flush();
      sessionFile.close();
    }
  }

  void CharacterEditorWindow::load()
  {
    // string to json
    std::string inputFile = "data/";
    //Replace whitespace in character name for filename
    std::string characterNameNoWhitespace{};
    if(!character_.name_.empty())
    {
      characterNameNoWhitespace = character_.name_;
    }
    else
    {
      characterNameNoWhitespace = "no_name";
    }
    //Temp for ease of use while development
    characterNameNoWhitespace = "Hula_Steelheart";
    std::ranges::replace(characterNameNoWhitespace, ' ', '_');
    inputFile += characterNameNoWhitespace + "_character_sheet" +  ".json";

    std::string jsonFileContents = readFromFile(inputFile);
    nlohmann::json jsonFromFile = nlohmann::json::parse(jsonFileContents);

    character_ = jsonFromFile.get<Character>();
  }

  void CharacterEditorWindow::buildAbilityScoreUiItem(const std::string& ability, float sameLineDistance, float inputFieldWidth)
  {
    ImGui::Text("%s", (ability + ": ").c_str());
    ImGui::SameLine(sameLineDistance);
    ImGui::PushItemWidth(inputFieldWidth);

    std::string inputFieldId = "##char_edit_" + ability + "_attrib";
    int& valueFieldReference = character_.abilityScores_.at(ability);

    ImGui::InputInt(inputFieldId.c_str(), &valueFieldReference);
    character_.abilityScores_.at(ability) = std::min(static_cast<int>(DndData::abilities_.maxAbilityScore_), std::max(1, valueFieldReference));
    ImGui::PopItemWidth();

    ImGui::SameLine(sameLineDistance + inputFieldWidth + 15);
    std::string modifierValue = "Modifier:  " + std::to_string(DndData::abilities_.abilityScoreToModifiers_.at(valueFieldReference));
    ImGui::Text("%s", modifierValue.c_str());
  }
} // Dnd