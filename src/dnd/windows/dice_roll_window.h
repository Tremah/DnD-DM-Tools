#pragma once
#ifndef DND_DM_TOOLS_DICE_ROLL_WINDOW_H
#define DND_DM_TOOLS_DICE_ROLL_WINDOW_H

#include <dnd/windows/window.h>

#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_map>
#include <random>

namespace Dnd
{
  /**
     *  \brief  Struct to simulate a die.
     *
     *  Contains name, number of sides and the maximum score on the die.
     */
  struct Dice
  {
    Dice() = default;
    Dice(uint32_t maxScore) : maxScore_{maxScore} {}

    uint32_t maxScore_ = 0;
  };

  /**
     *  \brief  Struct to simulate rolling a die.
     *
     *  Contains the rolled die and the score.
     */
  struct DiceRoll
  {
    DiceRoll(Dice die, bool queued = false) : die_{std::move(die)}, queued_{queued} {}

    Dice die_{};
    uint32_t score_ = 0;
    bool queued_ = false;

    //ImGui flags
    bool resultWindowOpen_ = false;

    /**
      *  \brief  Rolls the dice.
      *
      *  Determines a random number between 1 and maxScore_.
      *
      *  \return Random number between 1 and maxScore_.
      */
    int roll()
    {
      std::mt19937 random_engine(std::random_device{}());
      std::uniform_int_distribution<int> rngX(1, die_.maxScore_);

      score_ = rngX(random_engine);
      return score_;
    }
  };

  class DiceRollWindow : public Window
  {
  public:
    DiceRollWindow();

    void init() override;
    void update() override;
    void shutdown() override;

  private:
    std::vector<Dice> dice_{};
    std::vector<DiceRoll> diceRollQueue_{};
    std::unordered_map<int, std::vector<DiceRoll>> diceRollHistory_{};


    //ImGui related fields
    bool d20ResultWindowOpen = false;

    bool windowOpen_ = true;
    std::unordered_map<std::size_t, uint32_t> diceRollCounterState_{};

    void addRollToQueue(const Dice& die);
  };

} // Dnd

#endif //DND_DM_TOOLS_DICE_ROLL_WINDOW_H
