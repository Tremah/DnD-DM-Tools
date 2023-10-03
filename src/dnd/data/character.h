#pragma once
#ifndef DND_DM_TOOLS_CHARACTER_H
#define DND_DM_TOOLS_CHARACTER_H

#include <dnd/data/creature.h>

namespace Dnd
{
  struct Character : public Creature
  {
    Character() = default;
    Character(const std::string& name, int age, int level, const std::string& race, const std::string& clazz, const std::string& alignment) : Creature(name, age, level, race, clazz, alignment) {}

    int xp_ = 0;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Character, name_, age_, level_, race_, class_, alignment_, xp_)
  };

} // Dnd

#endif //DND_DM_TOOLS_CHARACTER_H
