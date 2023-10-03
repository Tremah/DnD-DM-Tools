#pragma once
#ifndef DND_DM_TOOLS_CHARACTER_EDITOR_WINDOW_H
#define DND_DM_TOOLS_CHARACTER_EDITOR_WINDOW_H

#include <dnd/windows//window.h>
#include <dnd/data/character.h>

namespace Dnd
{
  class CharacterEditorWindow : public Window
  {
  public:
    CharacterEditorWindow() = default;

    void init() override;
    void update() override;
    void shutdown() override;

  private:
    Character character_{};

    void save();
    void load();

    void buildAbilityScoreUiItem(const std::string& ability, float sameLineDistance, float inputFieldWidth = 100.f);


  };

} // Dnd

#endif //DND_DM_TOOLS_CHARACTER_EDITOR_WINDOW_H
