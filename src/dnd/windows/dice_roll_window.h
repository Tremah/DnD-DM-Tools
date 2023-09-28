#pragma once
#ifndef DND_DM_TOOLS_DICE_ROLL_WINDOW_H
#define DND_DM_TOOLS_DICE_ROLL_WINDOW_H

#include <dnd/windows/window.h>

#include <string>
#include <utility>
#include <chrono>
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
    DiceRoll() = default;
    explicit DiceRoll(Dice die, uint32_t numRolls, bool queued = false);

    Dice die_{};
    //How many rolls with this dice are supposed to be done
    uint32_t numRolls_ = 0;
    std::vector<uint32_t> scores_{};
    std::chrono::time_point<std::chrono::system_clock> rollTime_{};
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
    void roll();
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
    std::unordered_map<std::size_t, uint32_t> diceRollCounterState_{};
    std::unordered_map<std::size_t, bool> diceShowStatisticsWindowState_{};
    std::vector<DiceRoll> diceRollHistoryVector_{};

    //Last roll that was done by clicking a roll button
    DiceRoll lastRoll_{};



    //ImGui related fields
    bool d20ResultWindowOpen = false;

    bool windowOpen_ = true;

    bool d20ShowStatistics = false;

    void addRollToQueue(const Dice& die);
  };

} // Dnd

#endif //DND_DM_TOOLS_DICE_ROLL_WINDOW_H
