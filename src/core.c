#include "core.h"

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
	return fast_rand()%sides + 1;
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
	}
}
