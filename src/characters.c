#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "magick.h"

void init_dormarian(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	character->race = RACE_ELF;

	strcpy(character->name, "Dormarian");

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 39;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 35;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 31;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 38;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 53;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 47;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 46;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 55;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 48;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 32;

	character->characteristic_advances[CHARACTERISTIC_WEAPONS_SKILL] = 11;
	character->characteristic_advances[CHARACTERISTIC_TOUGHNESS] = 2;
	character->characteristic_advances[CHARACTERISTIC_AGILITY] = 10;
	character->characteristic_advances[CHARACTERISTIC_INTELLIGENCE] = 15;
	character->characteristic_advances[CHARACTERISTIC_WILLPOWER] = 14;

	character->skill_advances[SKILL_LANGUAGE_MAGICK] = 14;
	character->skill_advances[SKILL_CHANNELING_ULGU] = 20;

	character->talents[TALENT_ARCANE_MAGICK_ULGU] = 1;
	character->talents[TALENT_INSTINCTIVE_DICTION] = 1;
	character->talents[TALENT_AETHYRIC_ATTUNEMENT_ULGU] = 1;
	character->talents[TALENT_LUCK] = 1;

	character->trappings[TRAPPING_MAGICK_STICK_ULGU] = 1;
	character->trappings[TRAPPING_MAGICK_KEY_ULGU] = 1;
	character->trappings[TRAPPING_MAGICK_KEY_SHYSH] = 1;
	character->trappings[TRAPPING_MAGICK_KEY_HYSH] = 1;
	character->trappings[TRAPPING_MAGICK_KEY_AQSHY] = 1;

	character->fate_points = 1;
	character->resilience_points = 2;

	character->ap_mundane = 1;
	character->ap_magical = 2;


	character->talents[TALENT_ARCANE_MAGICK_HYSH] = 1;

	// Speed of thought
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] += 20;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] += 20;
}

void init_bruno(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	strcpy(character->name, "Bruno");

	character->race = RACE_HUMAN;

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 33;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 28;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 30;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 35;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 53;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 37;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 30;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 39;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 37;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 22;

	character->characteristic_advances[CHARACTERISTIC_WEAPONS_SKILL] = 5;
	character->characteristic_advances[CHARACTERISTIC_TOUGHNESS] = 5;
	character->characteristic_advances[CHARACTERISTIC_INITIATIVE] = 5;
	character->characteristic_advances[CHARACTERISTIC_DEXTERITY] = 5;
	character->characteristic_advances[CHARACTERISTIC_INTELLIGENCE] = 5;
	character->characteristic_advances[CHARACTERISTIC_WILLPOWER] = 5;

	character->skill_advances[SKILL_LANGUAGE_MAGICK] = 15;
	character->skill_advances[SKILL_CHANNELING_ULGU] = 5;

	character->talents[TALENT_ARCANE_MAGICK_ULGU] = 1;
	character->talents[TALENT_LUCK] = 1;

	character->trappings[TRAPPING_MAGICK_STICK_ULGU] = 1;

	character->fate_points = 1;
	character->resilience_points = 2;

}

void init_bruno_elder(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	strcpy(character->name, "Bruno");

	character->race = RACE_HUMAN;

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 33;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 28;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 30;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 35;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 53;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 37;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 30;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 39;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 37;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 22;

	character->characteristic_advances[CHARACTERISTIC_WEAPONS_SKILL] = 5;
	character->characteristic_advances[CHARACTERISTIC_TOUGHNESS] = 5;
	character->characteristic_advances[CHARACTERISTIC_INITIATIVE] = 5;
	character->characteristic_advances[CHARACTERISTIC_DEXTERITY] = 5;
	character->characteristic_advances[CHARACTERISTIC_INTELLIGENCE] = 5;
	character->characteristic_advances[CHARACTERISTIC_WILLPOWER] = 5;

	character->skill_advances[SKILL_LANGUAGE_MAGICK] = 15;
	character->skill_advances[SKILL_CHANNELING_ULGU] = 5;

	character->talents[TALENT_ARCANE_MAGICK_ULGU] = 1;
	character->talents[TALENT_LUCK] = 1;

	character->trappings[TRAPPING_MAGICK_STICK_ULGU] = 1;

	character->fate_points = 1;
	character->resilience_points = 2;

}

void init_dr_mccoy(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	strcpy(character->name, "Dr. McCoy");

	character->race = RACE_HUMAN;

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 33;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 28;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 30;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 36;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 53;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 37;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 30;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 57;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 42;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 22;

	character->characteristic_advances[CHARACTERISTIC_TOUGHNESS] = 0;
	character->characteristic_advances[CHARACTERISTIC_INITIATIVE] = 0;
	character->characteristic_advances[CHARACTERISTIC_DEXTERITY] = 0;
	character->characteristic_advances[CHARACTERISTIC_INTELLIGENCE] = 0;
	character->characteristic_advances[CHARACTERISTIC_WILLPOWER] = 0;

	character->skill_advances[SKILL_LANGUAGE_MAGICK] = 16;
	character->skill_advances[SKILL_CHANNELING_AQSHY] = 5;

	character->talents[TALENT_ARCANE_MAGICK_AQSHY] = 1;
	character->talents[TALENT_AETHYRIC_ATTUNEMENT_AQSHY] = 1;
	character->talents[TALENT_LUCK] = 1;

	character->trappings[TRAPPING_MAGICK_STICK_AQSHY] = 1;

	character->fate_points = 1;
	character->resilience_points = 2;

	character->ap_mundane = 1;
}
