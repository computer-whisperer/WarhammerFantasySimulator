/*
 * main.c
 *
 *  Created on: Jun 2, 2020
 *      Author: christian
 */

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

	character->characteristic_advances[CHARACTERISTIC_WEAPONS_SKILL] = 10;
	character->characteristic_advances[CHARACTERISTIC_TOUGHNESS] = 2;
	character->characteristic_advances[CHARACTERISTIC_AGILITY] = 10;
	character->characteristic_advances[CHARACTERISTIC_INTELLIGENCE] = 11;
	character->characteristic_advances[CHARACTERISTIC_WILLPOWER] = 12;

	character->skill_advances[SKILL_LANGUAGE_MAGICK] = 13;
	character->skill_advances[SKILL_CHANNELING_ULGU] = 15;

	character->talents[TALENT_INSTINCTIVE_DICTION] = 1;
	character->talents[TALENT_AETHYRIC_ATTUNEMENT] = 1;
	character->talents[TALENT_LUCK] = 1;

	character->fate_points = 1;
	character->resilience_points = 2;

	character->ap = 3;
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

	character->characteristic_advances[CHARACTERISTIC_TOUGHNESS] = 5;
	character->characteristic_advances[CHARACTERISTIC_INITIATIVE] = 5;
	character->characteristic_advances[CHARACTERISTIC_DEXTERITY] = 5;
	character->characteristic_advances[CHARACTERISTIC_INTELLIGENCE] = 1;
	character->characteristic_advances[CHARACTERISTIC_WILLPOWER] = 3;

	character->skill_advances[SKILL_LANGUAGE_MAGICK] = 10;
	character->skill_advances[SKILL_CHANNELING_ULGU] = 10;

	character->talents[TALENT_LUCK] = 1;

	character->fate_points = 1;
	character->resilience_points = 2;

	character->ap = 0;
}

void init_nasty(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	character->race = RACE_HUMAN;

	strcpy(character->name, "Nasty");

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

	character->characteristic_advances[CHARACTERISTIC_TOUGHNESS] = 15;
	character->characteristic_advances[CHARACTERISTIC_INITIATIVE] = 5;
	character->characteristic_advances[CHARACTERISTIC_DEXTERITY] = 5;
	character->characteristic_advances[CHARACTERISTIC_INTELLIGENCE] = 1;
	character->characteristic_advances[CHARACTERISTIC_WILLPOWER] = 3;

	character->skill_advances[SKILL_LANGUAGE_MAGICK] = 0;
	character->skill_advances[SKILL_CHANNELING_ULGU] = 0;

	character->talents[TALENT_LUCK] = 1;

	character->fate_points = 1;
	character->resilience_points = 2;

	character->ap = 4;
}

void init_nasty_caster(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	character->race = RACE_HUMAN;

	strcpy(character->name, "Nasty Caster");

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 33;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 28;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 30;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 35;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 53;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 37;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 30;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 49;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 47;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 22;

	character->characteristic_advances[CHARACTERISTIC_TOUGHNESS] = 5;
	character->characteristic_advances[CHARACTERISTIC_INITIATIVE] = 5;
	character->characteristic_advances[CHARACTERISTIC_DEXTERITY] = 5;
	character->characteristic_advances[CHARACTERISTIC_INTELLIGENCE] = 1;
	character->characteristic_advances[CHARACTERISTIC_WILLPOWER] = 3;

	character->skill_advances[SKILL_LANGUAGE_MAGICK] = 10;
	character->skill_advances[SKILL_CHANNELING_ULGU] = 10;

	character->talents[TALENT_LUCK] = 1;

	character->fate_points = 1;
	character->resilience_points = 2;

	character->ap = 0;
}

#define NUM_ITERATIONS 100000

void report_engagement(struct ENGAGEMENT_T * engagement)
{
	printf("  Damage per round: %f\n", ((float)engagement->damage_applied)/((float)engagement->rounds));
	printf("  Mean SL on success: %f\n", ((float)engagement->total_cast_sls)/((float)engagement->total_cast_successes));
	printf("  Mean overcasts on success: %f\n", ((float)engagement->total_cast_overcasts)/((float)engagement->total_cast_successes));
	printf("  Minor Misscasts per round: %f\n", ((float)engagement->minor_misscasts)/((float)engagement->rounds));
	printf("  Major Misscasts per round: %f\n", ((float)engagement->major_misscasts)/((float)engagement->rounds));

}

void report_character(struct CHARACTER_T * character)
{
	printf("%s:\n", character->name);
	printf("  Toughness: %d \n", GET_CHARACTERISTIC(character, CHARACTERISTIC_TOUGHNESS));
	printf("  Intelligence: %d \n", GET_CHARACTERISTIC(character, CHARACTERISTIC_INTELLIGENCE));
	printf("  Willpower: %d \n", GET_CHARACTERISTIC(character, CHARACTERISTIC_WILLPOWER));
	printf("  Language Magick: %d \n", GET_SKILL(character, SKILL_LANGUAGE_MAGICK));
	printf("  Channeling (Ulgu): %d \n", GET_SKILL(character, SKILL_CHANNELING_ULGU));
	printf("  Channeling (Aqshy): %d \n", GET_SKILL(character, SKILL_CHANNELING_AQSHY));
	printf("  AP: %d \n", character->ap);
	printf("  Talents:\n");
	if (character->talents[TALENT_AETHYRIC_ATTUNEMENT])
	{
		printf("    Aethyric Attunement %d\n", character->talents[TALENT_AETHYRIC_ATTUNEMENT]);
	}
	if (character->talents[TALENT_INSTINCTIVE_DICTION])
	{
		printf("    Instinctive Diction %d\n", character->talents[TALENT_INSTINCTIVE_DICTION]);
	}

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
}

int main (int argc, char * argv[])
{
	struct CHARACTER_T dormarian;
	init_dormarian(&dormarian);
	reset_character(&dormarian);

	struct CHARACTER_T bruno;
	init_bruno(&bruno);
	reset_character(&bruno);

	struct CHARACTER_T nasty;
	init_nasty(&nasty);
	reset_character(&nasty);

	struct CHARACTER_T nasty_caster;
	init_nasty_caster(&nasty_caster);
	reset_character(&nasty_caster);

	struct ENGAGEMENT_T engagement;
	engagement.aggressor = &bruno;
	engagement.defender = &nasty;
	engagement.num_defenders = 10;
	engagement.magick_bonus = 10;
	engagement.dispel_bonus_sl = 0;
	reset_engagement(&engagement);

	printf("Engagement:\n");
	printf("  Num Defenders: %d\n", engagement.num_defenders);
	printf("  Magick Bonus: %d\n", engagement.magick_bonus);
	printf("  Dispel Bonus: %d\n", engagement.dispel_bonus_sl);
	printf("\n");

	printf("Aggressor: ");
	report_character(engagement.aggressor);
	printf("\n");

	printf("Defender: ");
	report_character(engagement.defender);

	printf("\n\n");

	printf("Dart flat cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		cast_dart(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Bolt flat cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		cast_bolt(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Bolt channel 2 cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		if (engagement.sl_channeled < 2)
			channel(&engagement, MAGICK_TYPE_ULGU);
		else
			cast_bolt(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Blast flat cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		cast_blast(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Blast channel 2 cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		if (engagement.sl_channeled < 2)
			channel(&engagement, MAGICK_TYPE_ULGU);
		else
			cast_blast(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Shadow dagger flat cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		cast_shadow_dagger(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Shadow dagger channel 2 cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		if (engagement.sl_channeled < 2)
			channel(&engagement, MAGICK_TYPE_ULGU);
		else
			cast_shadow_dagger(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Shadow dagger w/ followup flat cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		cast_shadow_dagger_w_followup(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Shadow dagger w/ followup channel 2 cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		if (engagement.sl_channeled < 2)
			channel(&engagement, MAGICK_TYPE_ULGU);
		else
			cast_shadow_dagger_w_followup(&engagement, MAGICK_TYPE_ULGU);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Great Fires of Uzhul flat cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		cast_great_fires_of_uzhul(&engagement, MAGICK_TYPE_AQSHY);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Great Fires of Uzhul channel 4 cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		if (engagement.sl_channeled < 4)
			channel(&engagement, MAGICK_TYPE_AQSHY);
		else
			cast_great_fires_of_uzhul(&engagement, MAGICK_TYPE_AQSHY);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Great Fires of Uzhul channel 8 cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		if (engagement.sl_channeled < 8)
			channel(&engagement, MAGICK_TYPE_AQSHY);
		else
			cast_great_fires_of_uzhul(&engagement, MAGICK_TYPE_AQSHY);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);

	printf("Great Fires of Uzhul channel 10 cast:\n");
	for (int i = 0; i < NUM_ITERATIONS; i++)
	{
		if (engagement.sl_channeled < 10)
			channel(&engagement, MAGICK_TYPE_AQSHY);
		else
			cast_great_fires_of_uzhul(&engagement, MAGICK_TYPE_AQSHY);
	}
	report_engagement(&engagement);

	printf("\n\n");
	reset_engagement(&engagement);
}
