#pragma once
#ifndef DND_DM_TOOLS_CREATURE_H
#define DND_DM_TOOLS_CREATURE_H

#include <string>
#include <unordered_map>
#include <utility>

#include <nlohmann/json.hpp>

#include <dnd/data/types.h>
#include <dnd/data/dnd_data.h>

namespace Dnd
{
  struct Creature
  {
    Creature(const Creature&) = default;
    Creature(Creature&&) noexcept = default;
    Creature& operator=(const Creature&) = default;
    Creature& operator=(Creature&&) noexcept = default;
    virtual ~Creature() = default;

    Creature();
    Creature(std::string name, int age, int level, std::string race, std::string clazz, std::string alignment) : name_{std::move(name)}, age_{age}, level_{level}, race_{std::move(race)}, class_{std::move(clazz)}, alignment_{std::move(alignment)} {}

    //Variables
    std::string name_{};
    int age_ = 0;
    int level_ = 1;
    int hp_ = 0;
    std::string race_{};
    std::string class_{};
    std::string alignment_{};
    std::unordered_map<std::string, int> abilityScores_{};
    int proficiencyBonus_ = 0;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Creature, name_, age_, level_, hp_, race_, class_, alignment_, abilityScores_)
  };
} // Dnd

#endif //DND_DM_TOOLS_CREATURE_H
