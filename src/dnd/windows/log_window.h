#pragma once
#ifndef DND_WINDOW_LOG_WINDOW_H
#define DND_WINDOW_LOG_WINDOW_H

#include <string>
#include <vector>

#include <dnd/windows/window.h>

namespace Dnd
{
  class LogWindow : public Window
  {
  public:
    LogWindow();

    void init() override;
    void update() override;
    void shutdown() override;

    void addEntry(const std::string& entry);
    void addEmptyLine();
    void clearLog();
    const std::vector<std::pair<std::string, bool>>& getLogHistory() const;

  private:
    //Paired with bool, so entries can be made invisible without
    //deleting or moving them to another container
    std::vector<std::pair<std::string, bool>> logHistory_{};
  };

} // Dnd

#endif //DND_WINDOW_LOG_WINDOW_H
