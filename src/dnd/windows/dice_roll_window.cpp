#include "dice_roll_window.h"

#include <vector>
#include <iostream>

#include <imgui/imgui.h>

namespace Dnd
{
  DiceRollWindow::DiceRollWindow() : Window()
  {
    //Define available dice
    dice_.emplace_back(4);
    dice_.emplace_back(6);
    dice_.emplace_back(8);
    dice_.emplace_back(10);
    dice_.emplace_back(12);
    dice_.emplace_back(20);
    dice_.emplace_back(100);

    //Init dice-roll history
    diceRollHistory_.insert({4, std::vector<DiceRoll>{}});
    diceRollHistory_.insert({6, std::vector<DiceRoll>{}});
    diceRollHistory_.insert({8, std::vector<DiceRoll>{}});
    diceRollHistory_.insert({10, std::vector<DiceRoll>{}});
    diceRollHistory_.insert({12, std::vector<DiceRoll>{}});
    diceRollHistory_.insert({20, std::vector<DiceRoll>{}});
    diceRollHistory_.insert({100, std::vector<DiceRoll>{}});

    //Init dice-roll counter states
    diceRollCounterState_.insert({4, 1u});
    diceRollCounterState_.insert({6, 1u});
    diceRollCounterState_.insert({8, 1u});
    diceRollCounterState_.insert({10, 1u});
    diceRollCounterState_.insert({12, 1u});
    diceRollCounterState_.insert({20, 1u});
    diceRollCounterState_.insert({100, 1u});
  }

  void DiceRollWindow::update()
  {
    if(!ImGui::Begin("Dice Roll"))
    {
      //Window is collapsed or closed
      ImGui::End();
    }
    else
    {
      float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
      ImGui::AlignTextToFramePadding();
      ImGui::PushButtonRepeat(true);

      //Build dice roll ui elements
      for(auto& die : dice_)
      {
        std::string dieName = "d" + std::to_string(die.maxScore_);
        if(ImGui::CollapsingHeader(dieName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
          std::string arrowDownName = dieName + "ArrowDown";
          if (ImGui::ArrowButton(arrowDownName.c_str(), ImGuiDir_Left))
          {
            //Negative values
            diceRollCounterState_.at(die.maxScore_) = std::max(1u, --diceRollCounterState_.at(die.maxScore_));
          }
          ImGui::SameLine(0.0f, spacing);

          std::string arrowUpName = dieName + "ArrowUp";
          if (ImGui::ArrowButton(arrowUpName.c_str(), ImGuiDir_Right))
          {
            ++diceRollCounterState_.at(die.maxScore_);
          }
          ImGui::SameLine();
          ImGui::Text("%d", diceRollCounterState_.at(die.maxScore_));
          ImGui::SameLine();

          std::string buttonName = "Roll " + dieName;
          if (ImGui::Button(buttonName.c_str(), ImVec2{100, 0}))
          {
            std::cout << dieName << std::endl;
            if(diceRollCounterState_.at(die.maxScore_) > 0)
            {
              DiceRoll roll{Dice{die.maxScore_}};
              roll.roll();
              roll.resultWindowOpen_ = true;
              diceRollHistory_.at(die.maxScore_).emplace_back(std::move(roll));
            }
          }
          ImGui::Dummy(ImVec2{0, 5});

          auto tableStyleFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_PadOuterX;

          //Result table for each die
          std::string tableName = dieName + "ResultTable";
          if (ImGui::BeginTable(tableName.c_str(), 2, tableStyleFlags))
          {
            //Gather information about the roll history
            int lastRoll = -1;
            std::string lastFiveRoles{};
            auto& rollHistory = diceRollHistory_.at(die.maxScore_);

            if(!rollHistory.empty())
            {
              lastRoll = rollHistory.back().score_;
              auto loopUpperEnd = rollHistory.size() <= 5 ? rollHistory.size() : 5;
              for(std::size_t i = 0; i < loopUpperEnd; ++i)
              {
                lastFiveRoles.append(std::to_string(rollHistory.at(rollHistory.size() - 1 - i).score_));
                if(i < loopUpperEnd - 1)
                {
                  lastFiveRoles.append(", ");
                }
              }
            }

            //Display data
            std::string leftColumnValue{};
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Last Roll");
            ImGui::TableNextColumn();
            leftColumnValue = std::to_string(lastRoll);
            if(lastRoll < 0)
            {
              leftColumnValue.clear();
            }
            ImGui::Text("%s",  leftColumnValue.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("Last Five Rolls");
            ImGui::TableNextColumn();
            ImGui::Text("%s",  lastFiveRoles.c_str());
            ImGui::TableNextColumn();
            leftColumnValue = "Total Number Of " + dieName + "Rolls";
            ImGui::Text("Total Number Of  Rolls");
            ImGui::TableNextColumn();
            ImGui::Text("%d",  rollHistory.size());

            ImGui::EndTable();
          }

          //Padding between each die
          ImGui::Dummy(ImVec2{0, 5});
          ImGui::Separator();
          ImGui::Dummy(ImVec2{0, 5});



        }
      }
      ImGui::PopButtonRepeat();





      /*if(d20ResultWindowOpen)
      {
        ImGui::SetNextWindowSize(ImVec2{300, 80 + (static_cast<float>(1) * 25.f)});
        if (!ImGui::Begin("d20 Result Table", &d20ResultWindowOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
        {
          ImGui::End();
        }
        else
        {
          if (!diceRollHistory_.at(20).empty())
          {
            //Retrieve dice roll from history
            auto& roll = diceRollHistory_.at(20).back();

            ImGui::Dummy(ImVec2(0.0f, 1.0f));
            auto tableStyleFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_PadOuterX;

            if (ImGui::BeginTable("d20ResultTable", 2, tableStyleFlags))
            {
              ImGui::TableSetupColumn("Roll #");
              ImGui::TableSetupColumn("Score");
              ImGui::TableHeadersRow();

              std::size_t rowCount = 1;
              for (std::size_t i = 1; i <= rowCount; ++i)
              {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", std::to_string(i).c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%d",  roll.score_);
              }
              ImGui::EndTable();
              ImGui::Dummy(ImVec2(0.0f, 1.0f));
            }
          }
          ImGui::End();
        }
      }*/
    }
    ImGui::End();
  }

  void DiceRollWindow::shutdown()
  {

  }

  void DiceRollWindow::addRollToQueue(const Dice& die)
  {
    diceRollQueue_.emplace_back(die, true);
  }

  void DiceRollWindow::init()
  {

  }
} // Dnd