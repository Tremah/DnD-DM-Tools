#pragma once
#ifndef DND_DM_TOOLS_PARTY_OVERVIEW_WINDOW_H
#define DND_DM_TOOLS_PARTY_OVERVIEW_WINDOW_H

#include <dnd/windows/window.h>
#include <dnd/utility.h>

namespace Dnd
{

  class PartyOverviewWindow : public Window
  {
  public:
    PartyOverviewWindow() : Window(true) {}

    void init() override;
    void update() override;
    void shutdown() override;

  private:
    CsvValues characterProperties_{};
  };

} // Dnd

#endif //DND_DM_TOOLS_PARTY_OVERVIEW_WINDOW_H
