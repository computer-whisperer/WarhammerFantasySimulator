/*
 * main.c
 *
 *  Created on: Jun 2, 2020
 *      Author: christian
 */
#include <stdio.h>
#include "core.h"
#include "magick.h"
#include "characters.h"
#include "baddies.h"

int main (int argc, char * argv[])
{
	struct CHARACTER_T aggressor, defender;
	init_dormarian(&aggressor);
	init_crypt_ghoul(&defender);

	struct ENGAGEMENT_T engagement;
	engagement.aggressor = &aggressor;
	engagement.defender = &defender;
	engagement.num_defenders = 1;
	engagement.magick_bonus = 0;
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

	enum MAGICK_TYPE_T main_type = MAGICK_TYPE_ULGU;

	explore_spell(cast_dart, "Dart", &engagement, main_type);
	explore_spell(cast_bolt, "Bolt", &engagement, main_type);
	explore_spell(cast_blast, "Blast", &engagement, main_type);
	explore_spell(cast_shadow_dagger_v2, "Shadow Dagger", &engagement, main_type);
	explore_spell(cast_banishment, "Banishment", &engagement, MAGICK_TYPE_HYSH);
	explore_spell(cast_great_fires_of_uzhul, "Great Fires of Uzhul", &engagement, MAGICK_TYPE_AQSHY);
	explore_spell(cast_chain_attack, "Chain Attack", &engagement, MAGICK_TYPE_ULGU);
	explore_spell(cast_chain_attack, "Chain Attack", &engagement, MAGICK_TYPE_HYSH);
}
