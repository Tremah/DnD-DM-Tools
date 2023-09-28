#pragma once
#ifndef DND_DM_TOOLS_MENU_WINDOW_H
#define DND_DM_TOOLS_MENU_WINDOW_H

#include <dnd/windows/window.h>

namespace Dnd
{
  class MenuWindow : public Window
  {
  public:
    MenuWindow(bool& isAppRunning) : isAppRunning_{isAppRunning} {}

    void init() override;
    void update() override;
    void shutdown() override;
  private:
    //Owned by the main function, is set on false by clicking
    //the close button within the menu bar
    bool& isAppRunning_;

  };

} // Dnd

#endif //DND_DM_TOOLS_MENU_WINDOW_H
