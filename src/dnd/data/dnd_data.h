#pragma once
#ifndef DND_DM_TOOLS_DND_DATA_H
#define DND_DM_TOOLS_DND_DATA_H

#include <vector>
#include <string>
#include <tuple>

namespace Dnd
{
  struct Alignment
  {
    Alignment();

    //Alignment contains a name and a description
    //i.e. Chaotic Neutral (Description)
    std::vector<std::pair<std::string, std::string>> alignments_{};
  };

  struct Race
  {
    Race();
    std::vector<std::string> races_{};
    std::size_t raceCount_ = 10;
  };

  struct Class
  {
    Class();
    std::vector<std::string> classes_{};
    std::size_t classCount_ = 13;
  };

  struct Ability
  {
    Ability();

    std::vector<std::string> abilities_{};
    std::vector<int> abilityScoreToModifiers_{};
    std::size_t abilityCount_ = 6;
    std::size_t maxAbilityScore_ = 20;
  };

  struct Skill
  {
    Skill();

    std::vector<std::string> skills_{};
    std::vector<std::pair<std::string, std::string>> skillsToAbilities_{};
    std::size_t skillCount_ = 18;
  };

  /**
  *  \brief Contains all data relevant to D&D.
  *
  *  Contains a static instance of each data type the D&D rule set uses.
  */
  struct DndData
  {
    inline static Race race_{};
    inline static Class class_{};
    inline static Alignment alignment_{};
    inline static Ability abilities_{};
  };

} // Dnd

#endif //DND_DM_TOOLS_DND_DATA_H
