#pragma once
#ifndef DND_DM_TOOLS_COMBAT_WINDOW_H
#define DND_DM_TOOLS_COMBAT_WINDOW_H

#include <dnd/windows/window.h>

namespace Dnd
{
  class CombatWindow : public Window
  {
  public:
    CombatWindow() = default;

    void init() override;
    void update() override;
    void shutdown() override;
  };

} // Dnd

#endif //DND_DM_TOOLS_COMBAT_WINDOW_H
