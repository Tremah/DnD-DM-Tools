#include "log_window.h"

#include <format>
#include <chrono>

#include <imgui/imgui.h>

namespace Dnd
{
  LogWindow::LogWindow() : Window(true)
  {
    logHistory_.reserve(1000);
  }
  void LogWindow::init()
  {

  }

  void LogWindow::update()
  {
    if(!ImGui::Begin("LogWindow"))
    {
      ImGui::End();
    }
    else
    {
      ImGui::Dummy(ImVec2{0, 10});
      ImGui::Text("Session Log:");
      if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 25 * ImGui::GetTextLineHeightWithSpacing())))
      {
        for(const auto& entry : logHistory_)
        {
          if(!entry.second)
          {
            continue;
          }

          ImGui::Text("%s", entry.first.c_str());
          if(!entry.first.empty())
          {
            ImGui::Separator();
          }
        }
        ImGui::EndListBox();
        ImGui::Dummy(ImVec2{0.f, 10.f});
        if(ImGui::Button("Clear Log"))
        {
          clearLog();
        }
      }
      ImGui::End();
    }
  }

  void LogWindow::shutdown()
  {
  }

  void LogWindow::addEntry(const std::string& entry)
  {
    auto dateTimeString =  std::format("{:%H:%M:%OS}", std::chrono::system_clock::now());
    logHistory_.emplace_back(dateTimeString + ": " + entry, true);
  }

  void LogWindow::clearLog()
  {
    //Don't actually clear it but set every entry to not visible
    for(auto& entry : logHistory_)
    {
      entry.second = false;
    }
  }

  const std::vector<std::pair<std::string, bool>>& LogWindow::getLogHistory() const
  {
    return logHistory_;
  }

  void LogWindow::addEmptyLine()
  {
    logHistory_.emplace_back("", true);
  }
} // Dnd
