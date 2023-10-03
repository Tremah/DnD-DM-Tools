//
// Created by micro on 29/09/2023.
//

#include "dnd_data.h"

namespace Dnd
{
  Alignment::Alignment()
  {
    alignments_.reserve(10);
    alignments_.emplace_back("Unaligned", "A creature without the ability to make rational moral choices may be considered to have no alignment at all.");
    alignments_.emplace_back("Lawful Good (Crusader)", "A lawful good character is a protector. The iconic example of lawful good is a paladin, a holy knight who protects the weak and destroys evil.");
    alignments_.emplace_back("Neutral Good (Benefactor)", "A neutral good character believes in altruism over all else.");
    alignments_.emplace_back("Chaotic Good (Rebel)", "A Chaotic Good character believes in freedom as the highest virtue. The iconic example of chaotic good is Robin Hood, who rebels against authority as a way to protect the poor from poverty and suffering.");
    alignments_.emplace_back("Lawful Neutral (Judge)", "A lawful neutral character obeys principle as the highest virtue. For example, a judge who treats all fairly and equally would be considered lawful neutral.");
    alignments_.emplace_back("True Neutral (Undecided)", "A true neutral character is neutral on both axes, and cares not for any stance of alignment. This often describes someone who cares only for their own personal needs, neither inclined to hurt or harm others, nor to obey or rebel.");
    alignments_.emplace_back("Chaotic Neutral (Free Spirit)", "A chaotic neutral character follows their heart, but without the willingness to self-sacrifice as a chaotic good character might. A great many adventurers are chaotic neutral, doing what they wish and rejecting all forms of authority. Some chaotic neutral characters follow a deliberate philosophy of destroying the old to make way for the new.");
    alignments_.emplace_back("Lawful Evil (Dominator)", "A lawful evil character is a tyrant. They have no moral qualms about punishing individuals for the greater goal of furthering society. A lawful evil villain is often easy to deal with, as they can often be trusted to keep their word.");
    alignments_.emplace_back("Neutral Evil (Malefactor)", "A neutral evil character is selfish, and has no problem harming others to get what they want - if they can get away with it.");
    alignments_.emplace_back("Chaotic Evil (Destroyer)", "A chaotic evil character is malevolent. A villain bent on revenge might be of this alignment. Where the most powerful lawful evil villains might aim to conquer the world, this might be preferable to their chaotic evil counterparts, who would destroy it.");
  }

  Race::Race()
  {
    races_.reserve(10);
    races_.emplace_back("None");
    races_.emplace_back("Dwarf");
    races_.emplace_back("Elf");
    races_.emplace_back("Halfling");
    races_.emplace_back("Dragonborn");
    races_.emplace_back("Gnome");
    races_.emplace_back("Half-Elf");
    races_.emplace_back("Half-Orc");
    races_.emplace_back("Tiefling");
  }

  Class::Class()
  {
    classes_.reserve(13);
    classes_.emplace_back("None");
    classes_.emplace_back("Barbarian");
    classes_.emplace_back("Bard");
    classes_.emplace_back("Cleric");
    classes_.emplace_back("Druid");
    classes_.emplace_back("Fighter");
    classes_.emplace_back("Monk");
    classes_.emplace_back("Paladin");
    classes_.emplace_back("Ranger");
    classes_.emplace_back("Rogue");
    classes_.emplace_back("Sorcerer");
    classes_.emplace_back("Warlock");
    classes_.emplace_back("Wizard");
  }

  Ability::Ability()
  {
    abilities_.reserve(6);
    abilities_.emplace_back("Strength");
    abilities_.emplace_back("Dexterity");
    abilities_.emplace_back("Constitution");
    abilities_.emplace_back("Intelligence");
    abilities_.emplace_back("Wisdom");
    abilities_.emplace_back("Charisma");

    abilityScoreToModifiers_.reserve(59);
    abilityScoreToModifiers_.emplace_back(-5);
    abilityScoreToModifiers_.emplace_back(-5);
    abilityScoreToModifiers_.emplace_back(-4);
    abilityScoreToModifiers_.emplace_back(-4);
    abilityScoreToModifiers_.emplace_back(-3);
    abilityScoreToModifiers_.emplace_back(-3);
    abilityScoreToModifiers_.emplace_back(-2);
    abilityScoreToModifiers_.emplace_back(-2);
    abilityScoreToModifiers_.emplace_back(-1);
    abilityScoreToModifiers_.emplace_back(-1);
    abilityScoreToModifiers_.emplace_back(0);
    abilityScoreToModifiers_.emplace_back(0);
    abilityScoreToModifiers_.emplace_back(1);
    abilityScoreToModifiers_.emplace_back(1);
    abilityScoreToModifiers_.emplace_back(2);
    abilityScoreToModifiers_.emplace_back(2);
    abilityScoreToModifiers_.emplace_back(3);
    abilityScoreToModifiers_.emplace_back(3);
    abilityScoreToModifiers_.emplace_back(4);
    abilityScoreToModifiers_.emplace_back(4);
    abilityScoreToModifiers_.emplace_back(5);
    abilityScoreToModifiers_.emplace_back(5);
    abilityScoreToModifiers_.emplace_back(6);
    abilityScoreToModifiers_.emplace_back(6);
    abilityScoreToModifiers_.emplace_back(7);
    abilityScoreToModifiers_.emplace_back(7);
    abilityScoreToModifiers_.emplace_back(8);
    abilityScoreToModifiers_.emplace_back(8);
    abilityScoreToModifiers_.emplace_back(9);
    abilityScoreToModifiers_.emplace_back(9);
    abilityScoreToModifiers_.emplace_back(10);
  }

  Skill::Skill()
  {
    skills_.reserve(18);
    skills_.emplace_back("Acrobatics");
    skills_.emplace_back("Animal Handling");
    skills_.emplace_back("Arcana");
    skills_.emplace_back("Athletics");
    skills_.emplace_back("Deception");
    skills_.emplace_back("History");
    skills_.emplace_back("Insight");
    skills_.emplace_back("Intimidation");
    skills_.emplace_back("Investigation");
    skills_.emplace_back("Medicine");
    skills_.emplace_back("Nature");
    skills_.emplace_back("Perception");
    skills_.emplace_back("Performance");
    skills_.emplace_back("Persuasion");
    skills_.emplace_back("Religion");
    skills_.emplace_back("Sleight Of Hand");
    skills_.emplace_back("Stealth");
    skills_.emplace_back("Survival");

    skillsToAbilities_.reserve(18);
    skillsToAbilities_.emplace_back("Acrobatics", "Dexterity");
    skillsToAbilities_.emplace_back("Animal Handling", "Wisdom");
    skillsToAbilities_.emplace_back("Arcana", "Intelligence");
    skillsToAbilities_.emplace_back("Athletics", "Strength");
    skillsToAbilities_.emplace_back("Deception", "Charisma");
    skillsToAbilities_.emplace_back("History", "Intelligence");
    skillsToAbilities_.emplace_back("Insight", "Wisdom");
    skillsToAbilities_.emplace_back("Intimidation", "Charisma");
    skillsToAbilities_.emplace_back("Investigation", "Intelligence");
    skillsToAbilities_.emplace_back("Medicine", "Wisdom");
    skillsToAbilities_.emplace_back("Nature", "Intelligence");
    skillsToAbilities_.emplace_back("Perception", "Wisdom");
    skillsToAbilities_.emplace_back("Performance", "Charisma");
    skillsToAbilities_.emplace_back("Persuasion", "Charisma");
    skillsToAbilities_.emplace_back("Religion", "Wisdom");
    skillsToAbilities_.emplace_back("Sleight Of Hand", "Dexterity");
    skillsToAbilities_.emplace_back("Stealth", "Dexterity");
    skillsToAbilities_.emplace_back("Survival", "Wisdom");

  }
} // Dnd