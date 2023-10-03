//
// Created by micro on 28/09/2023.
//

#include "creature.h"

namespace Dnd
{
  Creature::Creature()
  {
    int a = 8u;
    abilityScores_.reserve(DndData::abilities_.abilities_.size());
    for(const auto& ability : DndData::abilities_.abilities_)
    {
      abilityScores_.insert({ability, 0});
    }

    race_ = DndData::race_.races_.front();
    class_ = DndData::class_.classes_.front();
    alignment_ = DndData::alignment_.alignments_.front().first;
  }
} // Dnd