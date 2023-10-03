#include "dice_roll_window.h"

#include <iostream>

#include <imgui/imgui.h>
#include <dnd/imgui_config.h>
#include <dnd/dm_tool_app.h>

namespace Dnd
{
  DiceRollWindow::DiceRollWindow() : Window(true)
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

    //Init state for showing the dice statistics
    diceShowStatisticsWindowState_.insert({4, false});
    diceShowStatisticsWindowState_.insert({6, false});
    diceShowStatisticsWindowState_.insert({8, false});
    diceShowStatisticsWindowState_.insert({10, false});
    diceShowStatisticsWindowState_.insert({12, false});
    diceShowStatisticsWindowState_.insert({20, false});
    diceShowStatisticsWindowState_.insert({100, false});
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
          //Left and right arrow for the dice roll count
          std::string arrowDownName = dieName + "ArrowDown";
          if (ImGui::ArrowButton(arrowDownName.c_str(), ImGuiDir_Left))
          {
            //Min value == 1
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

          //Dice roll button
          std::string buttonName = "Roll " + dieName;
          if (ImGui::Button(buttonName.c_str(), ImVec2{90, 0}))
          {
            if(diceRollCounterState_.at(die.maxScore_) > 0)
            {
              lastRoll_ = DiceRoll{Dice{die.maxScore_}, diceRollCounterState_.at(die.maxScore_)};
              lastRoll_.roll();
              lastRoll_.resultWindowOpen_ = true;
              diceRollHistory_.at(die.maxScore_).emplace_back(lastRoll_);

              DmToolApp::get()->getLogWindow()->addEntry("Roll " + std::to_string(lastRoll_.numRolls_) + " d" + std::to_string(lastRoll_.die_.maxScore_));
              std::size_t rollCount = 0;
              for(auto& score : lastRoll_.scores_)
              {
                ++rollCount;
                std::string entry = "d" + std::to_string(lastRoll_.die_.maxScore_) + " roll " + std::to_string(rollCount) + ": " + std::to_string(score);
                DmToolApp::get()->getLogWindow()->addEntry(entry);
              }
              DmToolApp::get()->getLogWindow()->addEmptyLine();

              d20ResultWindowOpen = true;
            }
          }
          ImGui::SameLine();
          ImGui::Dummy(ImVec2{10, 0});
          ImGui::SameLine();

          //Dice show statistics window button
          bool showStatisticsWindow = diceShowStatisticsWindowState_.at(die.maxScore_);
          buttonName = "Show " + dieName + " Statistics";
          if(showStatisticsWindow)
          {
            buttonName = "Hide " + dieName + " Statistics";
          }

          if (ImGui::Button(buttonName.c_str(), ImVec2{160, 0}))
          {
            diceShowStatisticsWindowState_.at(die.maxScore_) = !showStatisticsWindow ;
          }

          ImGui::Dummy(ImVec2{0, 5});


          //Statistics table for each die
          if(showStatisticsWindow)
          {
            std::string tableName = dieName + "ResultTable";
            auto tableStyleFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Borders | ImGuiTableFlags_PadOuterX;
            if (ImGui::BeginTable(tableName.c_str(), 2, tableStyleFlags))
            {
              //Gather information about the roll history
              int lastScore = -1;
              auto& rollHistory = diceRollHistory_.at(die.maxScore_);
              std::string lastFiveScores{};

              if (!rollHistory.empty())
              {
                lastScore = rollHistory.back().scores_.back();
                auto maxScoresInList = 5u;
                uint16_t rollCount = 0;
                //Extract last 5 rolls into vector
                std::vector<uint32_t> scoreVector{};
                for (auto it = rollHistory.rbegin(); it < rollHistory.rend(); ++it)
                {
                  for (auto score : it->scores_)
                  {
                    scoreVector.push_back(score);
                    if (scoreVector.size() == maxScoresInList)
                    {
                      break;
                    }
                  }
                  if (scoreVector.size() >= maxScoresInList)
                  {
                    break;
                  }
                }

                uint16_t scoreCount = 0;
                maxScoresInList = maxScoresInList <= scoreVector.size() ? maxScoresInList : scoreVector.size();
                for (auto it = scoreVector.rbegin(); it < scoreVector.rend(); ++it)
                {
                  lastFiveScores.append(std::to_string(*it));

                  if (++scoreCount < maxScoresInList)
                  {
                    lastFiveScores.append(",");
                  }
                  else
                  {
                    break;
                  }
                }
              }

              //Display table for each die
              std::string rightColumnValue{};
              ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::Text("Last Roll");
              ImGui::TableNextColumn();
              rightColumnValue = std::to_string(lastScore);
              if (lastScore < 0)
              {
                rightColumnValue.clear();
              }
              ImGui::Text("%s", rightColumnValue.c_str());

              ImGui::TableNextColumn();
              ImGui::Text("Last Five Rolls");
              ImGui::TableNextColumn();
              ImGui::Text("%s", lastFiveScores.c_str());
              ImGui::TableNextColumn();

              rightColumnValue = "Total Number Of " + dieName + "Rolls";
              std::size_t rollCount = 0;
              for (auto it = rollHistory.rbegin(); it < rollHistory.rend(); ++it)
              {
                rollCount += it->scores_.size();
              }
              ImGui::Text("Total Number Of  Rolls");
              ImGui::TableNextColumn();
              ImGui::Text("%zu", rollCount);
              ImGui::EndTable();

              //Padding between each die row
              ImGui::Dummy(ImVec2{0, 5});
              ImGui::Separator();
              ImGui::Dummy(ImVec2{0, 5});
            }
          }
        }
      }
      ImGui::PopButtonRepeat();

      //Result window
      if(d20ResultWindowOpen)
      {
        ImGui::PushFont(ImGuiConfig::imGuiFonts_.at("Lato").at(ImGuiConfig::standardFontSize_ + 20));
        ImGui::SetNextWindowSize(ImVec2{800.f, 120.f + (lastRoll_.scores_.size() * ImGui::GetTextLineHeightWithSpacing())});
        if(!ImGui::Begin("Dice Roll Result Window", &d20ResultWindowOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking))
        {
          ImGui::End();
        }
        else
        {
          std::string dieName = "d" + std::to_string(lastRoll_.die_.maxScore_) + " Score: ";

          ImGui::Dummy(ImVec2{0, 25});
          auto tableStyleFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_PadOuterX;
          if (ImGui::BeginTable("DiceRollWindowResultTab", 3, tableStyleFlags))
          {
            std::size_t i = 0;
            for (auto& score : lastRoll_.scores_)
            {
              ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::Text("%zu", ++i);
              ImGui::TableNextColumn();
              ImGui::Text(dieName.c_str());
              ImGui::TableNextColumn();
              ImGui::Text("%d", score);
            }
            ImGui::EndTable();
          }
          ImGui::PopFont();
          ImGui::End();
        }
      }

      /*
      ImGui::Dummy(ImVec2{0, 10});
      ImGui::Text("Session Log:");
      if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 40 * ImGui::GetTextLineHeightWithSpacing())))
      {
        for(auto diceRoll = diceRollHistoryVector_.rbegin(); diceRoll < diceRollHistoryVector_.rend(); ++diceRoll)
        {
          for(auto score = diceRoll->scores_.rbegin(); score < diceRoll->scores_.rend(); ++score)
          {
            auto dateTimeString =  std::format("{:%H:%M:%OS}", diceRoll->rollTime_);

            std::string entryText = dateTimeString + ": Roll d" + std::to_string(diceRoll->die_.maxScore_) + ", score =  " + std::to_string(*score);
            if (ImGui::Selectable(entryText.c_str(), false))
              ;
            ImGui::Separator();

          }
        }
        ImGui::EndListBox();
        ImGui::Dummy(ImVec2{0.f, 10.f});
        if(ImGui::Button("Clear Log"))
        {

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

  void DiceRoll::roll()
  {
    std::mt19937 random_engine(std::random_device{}());
    std::uniform_int_distribution<int> rngX(1, die_.maxScore_);

    rollTime_ = std::chrono::system_clock::now();
    for(std::size_t i  = 0; i < numRolls_; ++i)
    {
      scores_.emplace_back(rngX(random_engine));
    }
  }

  DiceRoll::DiceRoll(Dice die, uint32_t numRolls, bool queued) : die_{die}, numRolls_{numRolls}, queued_{queued}
  {
    scores_.reserve(numRolls);
  }
} // Dnd