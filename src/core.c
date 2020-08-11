#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"

char * SKILL_T_NAMES[] = {
	"Language (Magick)",
	"Channeling (Ulgu)",
	"Channeling (Aqshy)",
	"Channeling (Hysh)",
	"Channeling (Shyish)",
	"Channeling (Ghur)",
	"Channeling (Azyr)",
	"Channeling (Chamon)",
	"Channeling (Ghyran)"
};

char* CHARACTERISTIC_T_NAMES[] = {
	"Weapons Skill",
	"Ballistic Skill",
	"Strength",
	"Toughness",
	"Initiative",
	"Agility",
	"Dexterity",
	"Intelligence",
	"Willpower",
	"Fellowship"
};

char * TALENT_T_NAMES[] = {
	"Instinctive Diction",
	"Aethyric Attunement (Ulgu)",
	"Aethyric Attunement (Aqshy)",
	"Aethyric Attunement (Hysh)",
	"Aethyric Attunement (Shysh)",
	"Aethyric Attunement (Ghur)",
	"Aethyric Attunement (Azyr)",
	"Aethyric Attunement (Chamon)",
	"Aethyric Attunement (Ghyran)",
	"Arcane Magick (Ulgu)",
	"Arcane Magick (Aqshy)",
	"Arcane Magick (Hysh)",
	"Arcane Magick (Shysh)",
	"Arcane Magick (Ghur)",
	"Arcane Magick (Azyr)",
	"Arcane Magick (Chamon)",
	"Arcane Magick (Ghyran)",
	"Luck",
	"Perfect Pitch"
};

char* TRAIT_T_NAMES[] = {
	"Undead",
	"Demonic"
};

char* TRAPPING_T_NAMES[] = {
	"Magick Stick (Evil)",
	"Magick Stick (Ulgu)",
	"Magick Stick (Aqshy)",
	"Magick Stick (Hysh)",
	"Magick Stick (Shysh)",
	"Magick Stick (Ghur)",
	"Magick Stick (Azyr)",
	"Magick Stick (Chamon)",
	"Magick Stick (Ghyran)",
	"Magick Key (Ulgu)",
	"Magick Key (Aqshy)",
	"Magick Key (Hysh)",
	"Magick Key (Shysh)",
	"Magick Key (Ghur)",
	"Magick Key (Azyr)",
	"Magick Key (Chamon)",
	"Magick Key (Ghyran)",
};

char* RACE_T_NAMES[] = {
	"Elf",
	"Human",
	"Other"
};

enum CHARACTERISTIC_T skill_to_char_map [SKILL_NUM_SKILLS] =
{
		CHARACTERISTIC_INTELLIGENCE,
		CHARACTERISTIC_WILLPOWER,
		CHARACTERISTIC_WILLPOWER,
		CHARACTERISTIC_WILLPOWER,
		CHARACTERISTIC_WILLPOWER,
		CHARACTERISTIC_WILLPOWER,
		CHARACTERISTIC_WILLPOWER,
		CHARACTERISTIC_WILLPOWER,
		CHARACTERISTIC_WILLPOWER
};

unsigned int g_seed = 1215;

// Compute a pseudorandom integer.
// Output value in range [0, 32767]
int fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0x7FFF;
}

int d(int sides)
{
	return (fast_rand()%sides) + 1;
}

void reset_character(struct CHARACTER_T * character)
{
	character->fortune_points = character->fate_points + character->talents[TALENT_LUCK];
	character->resolve_points = character->resilience_points;

	switch (character->race)
	{
		case RACE_ELF:
		case RACE_HUMAN:
			character->wounds_left = GET_CHARACTERISTIC_BONUS(character, CHARACTERISTIC_STRENGTH) + 2*GET_CHARACTERISTIC_BONUS(character, CHARACTERISTIC_TOUGHNESS) + GET_CHARACTERISTIC_BONUS(character, CHARACTERISTIC_WILLPOWER);
			break;
		default:
			character->wounds_left = character->beast_wounds;
	}
}

void report_character(struct CHARACTER_T * character)
{
	printf("%s:\n", character->name);
	printf("  Characteristics:\n");
	for (int i = 0; i < CHARACTERISTIC_NUM_CHARACTERISTICS; i++)
	{
		printf("    %s: %d \n", CHARACTERISTIC_T_NAMES[i], GET_CHARACTERISTIC(character, i));
	}
	printf("  Skills:\n");
	int c = 0;
	for (int i = 0; i < SKILL_NUM_SKILLS; i++)
	{
		if (character->skill_advances[i] > 0)
		{
			c++;
			printf("    %s: %d \n", SKILL_T_NAMES[i], GET_SKILL(character, i));
		}
	}
	if (c == 0)
	{
		printf("    (None)\n");
	}
	printf("  Talents:\n");
	c = 0;
	for (int i = 0; i < TALENT_NUM_TALENTS; i++)
	{
		if (character->talents[i] > 0)
		{
			c++;
			printf("    %s: %d \n", TALENT_T_NAMES[i], character->talents[i]);
		}
	}
	if (c == 0)
	{
		printf("    (None)\n");
	}
	printf("  Traits:\n");
	c = 0;
	for (int i = 0; i < TRAIT_NUM_TRAITS; i++)
	{
		if (character->traits[i] > 0)
		{
			c++;
			printf("    %s: %d \n", TRAIT_T_NAMES[i], character->traits[i]);
		}
	}
	if (c == 0)
	{
		printf("    (None)\n");
	}
	printf("  Trappings:\n");
	c = 0;
	for (int i = 0; i < TRAPPING_NUM_TRAPPINGS; i++)
	{
		if (character->trappings[i] > 0)
		{
			c++;
			printf("    %s: %d \n", TRAPPING_T_NAMES[i], character->trappings[i]);
		}
	}
	if (c == 0)
	{
		printf("    (None)\n");
	}
	printf("  Armor Points:\n");
	printf("    Mundane: %d \n", character->ap_mundane);
	printf("    Magical: %d \n", character->ap_magical);
	printf("    Shield: %d \n", character->ap_shield);
	printf("  Wounds left: %d \n", character->wounds_left);
}

void reset_engagement(struct ENGAGEMENT_T * engagement)
{
	engagement->damage_applied = 0;
	engagement->sl_channeled = 0;
	engagement->minor_misscasts = 0;
	engagement->major_misscasts = 0;
	engagement->rounds = 0;
	engagement->total_cast_sls = 0;
	engagement->total_cast_successes = 0;
	engagement->total_cast_overcasts = 0;

	engagement->round_of_last_success = 0;
	memset(engagement->gap_counters, 0, sizeof(engagement->gap_counters));

	reset_character(engagement->aggressor);
	reset_character(engagement->defender);
}
