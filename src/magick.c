#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "magick.h"

char* MAGICK_TYPE_T_NAMES[] = {
	"Ulgu",
	"Aqshy",
	"Hysh",
	"Shysh",
	"Ghur",
	"Azyr",
	"Chamon",
	"Ghyran"
};

enum SKILL_T magick_type_to_channel_skill[MAGICK_TYPE_NUM_TYPES] = {
		SKILL_CHANNELING_ULGU,
		SKILL_CHANNELING_AQSHY,
		SKILL_CHANNELING_HYSH,
		SKILL_CHANNELING_SHYISH,
		SKILL_CHANNELING_GHUR,
		SKILL_CHANNELING_AZYR,
		SKILL_CHANNELING_CHAMON,
		SKILL_CHANNELING_GHYRAN,
};

enum TALENT_T magick_type_to_arcane_talent[MAGICK_TYPE_NUM_TYPES] = {
		TALENT_ARCANE_MAGICK_ULGU,
		TALENT_ARCANE_MAGICK_AQSHY,
		TALENT_ARCANE_MAGICK_HYSH,
		TALENT_ARCANE_MAGICK_SHYSH,
		TALENT_ARCANE_MAGICK_GHUR,
		TALENT_ARCANE_MAGICK_AZYR,
		TALENT_ARCANE_MAGICK_CHAMON,
		TALENT_ARCANE_MAGICK_GHYRAN
};

enum TALENT_T magick_type_to_aethyric_attunement[MAGICK_TYPE_NUM_TYPES] = {
		TALENT_AETHYRIC_ATTUNEMENT_ULGU,
		TALENT_AETHYRIC_ATTUNEMENT_AQSHY,
		TALENT_AETHYRIC_ATTUNEMENT_HYSH,
		TALENT_AETHYRIC_ATTUNEMENT_SHYSH,
		TALENT_AETHYRIC_ATTUNEMENT_GHUR,
		TALENT_AETHYRIC_ATTUNEMENT_AZYR,
		TALENT_AETHYRIC_ATTUNEMENT_CHAMON,
		TALENT_AETHYRIC_ATTUNEMENT_GHYRAN
};

enum TRAPPING_T magick_type_to_magick_stick[MAGICK_TYPE_NUM_TYPES] = {
		TRAPPING_MAGICK_STICK_ULGU,
		TRAPPING_MAGICK_STICK_AQSHY,
		TRAPPING_MAGICK_STICK_HYSH,
		TRAPPING_MAGICK_STICK_SHYSH,
		TRAPPING_MAGICK_STICK_GHUR,
		TRAPPING_MAGICK_STICK_AZYR,
		TRAPPING_MAGICK_STICK_CHAMON,
		TRAPPING_MAGICK_STICK_GHYRAN,
};

enum TRAPPING_T magick_type_to_magick_key[MAGICK_TYPE_NUM_TYPES] = {
		TRAPPING_MAGICK_KEY_ULGU,
		TRAPPING_MAGICK_KEY_AQSHY,
		TRAPPING_MAGICK_KEY_HYSH,
		TRAPPING_MAGICK_KEY_SHYSH,
		TRAPPING_MAGICK_KEY_GHUR,
		TRAPPING_MAGICK_KEY_AZYR,
		TRAPPING_MAGICK_KEY_CHAMON,
		TRAPPING_MAGICK_KEY_GHYRAN
};

void cast_test(struct ENGAGEMENT_T * engagement, int cn, struct CAST_RESULT_T * result)
{
	struct CHARACTER_T * caster = engagement->aggressor;
	int roll = d(100);
	int base = GET_SKILL(caster, SKILL_LANGUAGE_MAGICK);
	base += engagement->magick_bonus;
	int bonus_on_success = 0;

	if (caster->trappings[TRAPPING_MAGICK_STICK_EVIL])
	{
		base += 40;
		bonus_on_success += 4;
	}
	else
	{
		for (int i = 0; i < MAGICK_TYPE_NUM_TYPES; i++)
		{
			if (caster->trappings[magick_type_to_magick_stick[i]])
			{
				base += 5;
				bonus_on_success = 2;
				break;
			}
		}
	}

	int delta = base - roll;
	result->is_critical = ((roll%100)/10 == roll%10);

	result->cn = cn;
	result->is_success = 0;

	if (delta < 0 || roll > AUTO_FAIL_HIGHER)
	{
		// Cast test fail
		if (result->is_critical || engagement->sl_channeled > 0)
		{
			engagement->minor_misscasts++;
		}
	}
	else
	{

		// Cast test success
		result->sl = delta / 10;
		result->sl += bonus_on_success;
		result->sl += caster->talents[TALENT_INSTINCTIVE_DICTION];
		result->sl += caster->talents[TALENT_PERFECT_PITCH];

		if (result->is_critical && (caster->talents[TALENT_INSTINCTIVE_DICTION] == 0))
		{
			engagement->minor_misscasts++;
		}

		if (engagement->sl_channeled > result->cn)
		{
			result->cn = 0;
		}
		else
		{
			result->cn -= engagement->sl_channeled;
		}

		if (result->is_critical && (result->sl < result->cn))
		{
			result->sl = result->cn;
		}

		// Now handle counterspell
		if (engagement->defender->skill_advances[SKILL_LANGUAGE_MAGICK] > 0)
		{
			int r2 = d(100);
			int b2 = GET_SKILL(engagement->defender, SKILL_LANGUAGE_MAGICK);
			b2 += engagement->magick_bonus;
			int d2 = b2 - r2;
			int sl2 = d2/10 + engagement->dispel_bonus_sl;
			if (sl2 > 0)
			{
				result->sl -= sl2;
			}
		}

		if (result->sl >= result->cn)
		{
			// Cast successful
			result->is_success = 1;
			result->overcasts = (result->sl - result->cn)/2;

			engagement->total_cast_successes++;
			engagement->total_cast_sls += result->sl;
			engagement->total_cast_overcasts += result->overcasts;

			// Check gap
			int gap = (engagement->rounds - engagement->round_of_last_success);
			for (int i = 0; i < GAP_TESTS; i++)
			{
				if (i < gap)
				{
					engagement->gap_counters[i] += gap;
				}
				else
				{
					break;
				}
			}

			engagement->round_of_last_success = engagement->rounds;
		}
	}
	engagement->sl_channeled = 0;

	engagement->rounds++;
}

void channel(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CHARACTER_T * caster = engagement->aggressor;
	int roll = d(100);
	int base = GET_SKILL(caster, magick_type_to_channel_skill[type]);
	base += engagement->magick_bonus;
	int delta = base - roll;
	int bonus_on_success = 0;

	if (caster->trappings[TRAPPING_MAGICK_STICK_EVIL])
	{
		base += 40;
		bonus_on_success += 4;
	}
	else if (caster->trappings[magick_type_to_magick_stick[type]])
	{
		base += 10;
		bonus_on_success = 2;
	}
	else if (caster->trappings[magick_type_to_magick_key[type]])
	{
		bonus_on_success = 1;
	}


	if ((roll%100)/10 == roll%10)
	{
		// Critical channel
		if (delta > 0 && roll <= AUTO_FAIL_HIGHER)
		{
			// Success
			engagement->sl_channeled = 100;
			if (caster->talents[magick_type_to_aethyric_attunement[type]] == 0)
			{
				engagement->minor_misscasts++;
			}
		}
		else
		{
			// Fail
			engagement->major_misscasts++;
		}
	}
	else
	{
		engagement->sl_channeled += delta/10;
		engagement->sl_channeled += bonus_on_success;

		if (delta > 0 && roll <= AUTO_FAIL_HIGHER)
		{
			engagement->sl_channeled += caster->talents[magick_type_to_aethyric_attunement[type]];
		}
	}

	if (engagement->sl_channeled < 0)
	{
		engagement->sl_channeled = 0;
	}

	engagement->rounds++;
}

void channel_to_sl(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type, int sl_target)
{
	int i = 0;
	while (engagement->sl_channeled < sl_target)
	{
		channel(engagement, type);
		i++;
		if (i > 20)
		{
			break;
		}
	}
}

#define NUM_ITERATIONS 100000

void explore_spell(CAST_FUNC_T spell, char* name, struct ENGAGEMENT_T * engagement_orig, enum MAGICK_TYPE_T type)
{
	// Short cut if we can't do it yet
	if (engagement_orig->aggressor->talents[magick_type_to_arcane_talent[type]] == 0)
	{
		return;
	}

	int best_channel_target = 0;
	float best_dpr = -1;
	float best_cpr = -1;
	struct ENGAGEMENT_T best_engagement;


	for (int channel_target = 0; channel_target < 20; channel_target++)
	{
		struct ENGAGEMENT_T engagement;
		memcpy(&engagement, engagement_orig, sizeof(engagement));

		for (int i = 0; i < NUM_ITERATIONS; i++)
		{
			channel_to_sl(&engagement, type, channel_target);
			spell(&engagement, type);
		}
		float dpr = ((float)engagement.damage_applied)/((float)engagement.rounds);
		float cpr = ((float)engagement.total_cast_successes)/((float)engagement.rounds);

		if (((dpr == best_dpr) && (cpr > best_cpr)) || (dpr > best_dpr))
		{
			// New best engagement
			best_channel_target = channel_target;
			best_dpr = dpr;
			best_cpr = cpr;
			memcpy(&best_engagement, &engagement, sizeof(engagement));
		}
	}
	// Report on best engagement
	printf("\n\nBest strategy for %s (%s):\n", name, MAGICK_TYPE_T_NAMES[type]);
	if (best_channel_target == 0)
	{
		printf("  Flat cast\n");
	}
	else
	{
		printf("  Channel to %d sl\n", best_channel_target);
	}
	printf("  Damage per round: %f\n", ((float)best_engagement.damage_applied)/((float)best_engagement.rounds));
	printf("  Success rate: %f\n", ((float)best_engagement.total_cast_successes)/((float)best_engagement.rounds));
	printf("  Mean SL on success: %f\n", ((float)best_engagement.total_cast_sls)/((float)best_engagement.total_cast_successes));
	printf("  Mean overcasts on success: %f\n", ((float)best_engagement.total_cast_overcasts)/((float)best_engagement.total_cast_successes));
	printf("  Minor Misscasts per round: %f\n", ((float)best_engagement.minor_misscasts)/((float)best_engagement.rounds));
	printf("  Major Misscasts per round: %f\n", ((float)best_engagement.major_misscasts)/((float)best_engagement.rounds));

	printf("  Success gaps:\n");
	for (int i = 1; i < GAP_TESTS; i++)
	{
		printf("    %d long or longer gaps per turn: %f\n", i, ((float)best_engagement.gap_counters[i]/((float)best_engagement.rounds)));
	}

}

void cast_dart(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CAST_RESULT_T result;
	cast_test(engagement, 0, &result);

	if (result.is_success)
	{
		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS) + engagement->defender->ap_mundane + engagement->defender->ap_magical;
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl;
		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
			if (damage > engagement->defender->wounds_left)
			{
				damage = engagement->defender->wounds_left;
			}

			int num_targets = 1 + result.overcasts;
			if (num_targets > engagement->num_defenders)
			{
				num_targets = engagement->num_defenders;
			}
			// Overcasts mean more targets
			engagement->damage_applied += damage*num_targets;
		}
	}
}

void cast_blast(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CAST_RESULT_T result;
	cast_test(engagement, 4, &result);

	if (result.is_success)
	{
		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS) + engagement->defender->ap_magical;
		if (type != MAGICK_TYPE_ULGU)
		{
			soak += engagement->defender->ap_mundane;
		}
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 3;

		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}

		if ((type == MAGICK_TYPE_HYSH) && (engagement->defender->traits[TRAIT_UNDEAD] || engagement->defender->traits[TRAIT_DEMONIC]))
		{
			damage += GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_INTELLIGENCE) + GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER);
		}

		if (damage > 0)
		{
			if (damage > engagement->defender->wounds_left)
			{
				damage = engagement->defender->wounds_left;
			}

			// Assume we hit 5 per overcast
			int num_targets = (1 + result.overcasts)*5;
			if (num_targets > engagement->num_defenders)
			{
				num_targets = engagement->num_defenders;
			}
			engagement->damage_applied += damage*num_targets;
		}
	}
}

void cast_bolt(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CAST_RESULT_T result;
	cast_test(engagement, 4, &result);

	if (result.is_success)
	{
		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS) + engagement->defender->ap_magical;
		if (type != MAGICK_TYPE_ULGU)
		{
			soak += engagement->defender->ap_mundane;
		}
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 4;

		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}

		if ((type == MAGICK_TYPE_HYSH) && (engagement->defender->traits[TRAIT_UNDEAD] || engagement->defender->traits[TRAIT_DEMONIC]))
		{
			damage += GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_INTELLIGENCE) + GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER);
		}

		if (damage > 0)
		{
			if (damage > engagement->defender->wounds_left)
			{
				damage = engagement->defender->wounds_left;
			}

			// Assume we hit 5 per overcast
			int num_targets = 1 + result.overcasts;
			if (num_targets > engagement->num_defenders)
			{
				num_targets = engagement->num_defenders;
			}
			engagement->damage_applied += damage*num_targets;
		}
	}
}

void cast_chain_attack(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CAST_RESULT_T result;
	cast_test(engagement, 6, &result);

	if (result.is_success)
	{
		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS) + engagement->defender->ap_magical;
		if ((type != MAGICK_TYPE_ULGU))
		{
			soak += engagement->defender->ap_mundane;
		}
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 4;

		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}

		if ((type == MAGICK_TYPE_HYSH) && (engagement->defender->traits[TRAIT_UNDEAD] || engagement->defender->traits[TRAIT_DEMONIC]))
		{
			damage += GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_INTELLIGENCE) + GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER);
		}

		if (damage > 0)
		{
			// We hit 1, do we hit more?
			int num_targets = 1;

			if (damage > engagement->defender->wounds_left)
			{
				damage = engagement->defender->wounds_left;
				num_targets += GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER) + (result.sl/2);
			}
			if (num_targets > engagement->num_defenders)
			{
				num_targets = engagement->num_defenders;
			}
			engagement->damage_applied += damage*num_targets;
		}
	}
}

void cast_shadow_dagger(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	if (type != MAGICK_TYPE_ULGU)
	{
		engagement->rounds++;
		return;
	}

	struct CAST_RESULT_T result;
	cast_test(engagement, 4, &result);

	if (result.is_success)
	{
		int toughness_ignore = 1 + result.overcasts;
		int max_toughness_ignore = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS)/2 + 1;
		if (toughness_ignore > max_toughness_ignore)
		{
			toughness_ignore = max_toughness_ignore;
		}

		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS);
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 2 + toughness_ignore;
		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
			int num_targets = 1;
			engagement->damage_applied += damage*num_targets;
		}
	}
}

void cast_shadow_dagger_w_followup(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	if (type != MAGICK_TYPE_ULGU)
	{
		engagement->rounds++;
		return;
	}

	struct CAST_RESULT_T result;
	cast_test(engagement, 4, &result);

	if (result.is_success)
	{
		int toughness_ignore = 1 + result.overcasts;
		int max_toughness_ignore = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS)/2 + 1;
		if (toughness_ignore > max_toughness_ignore)
		{
			toughness_ignore = max_toughness_ignore;
		}

		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS);
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 2 + toughness_ignore;
		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
			int num_targets = 1;
			engagement->damage_applied += damage*num_targets + toughness_ignore + engagement->defender->ap_mundane + engagement->defender->ap_magical + engagement->defender->ap_shield;
		}
	}
}

void cast_shadow_dagger_v2(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CAST_RESULT_T result;

	if (type != MAGICK_TYPE_ULGU)
	{
		engagement->rounds++;
		return;
	}

	cast_test(engagement, 4, &result);

	if (result.is_success)
	{
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 2;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
			int num_targets = 1;
			engagement->damage_applied += damage*num_targets + GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS) + engagement->defender->ap_mundane + engagement->defender->ap_magical + engagement->defender->ap_shield;
		}
	}
}


void cast_great_fires_of_uzhul(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CAST_RESULT_T result;
	if (type != MAGICK_TYPE_AQSHY)
	{
		engagement->rounds++;
		return;
	}

	cast_test(engagement, 10, &result);

	if (result.is_success)
	{
		// Primary attack
		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS);
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 10;
		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
			// Assume we hit 1 per overcast
			int num_targets = 1 + result.overcasts;
			if (num_targets > engagement->num_defenders)
			{
				num_targets = engagement->num_defenders;
			}
			engagement->damage_applied += damage*num_targets;

			// Secondary targets
			int num_secondary_targets = (1 + result.overcasts)*5;
			if (num_secondary_targets > engagement->num_defenders)
			{
				num_secondary_targets = engagement->num_defenders;
			}
			engagement->damage_applied += (GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 5)*num_secondary_targets;

		}
	}
}

void cast_banishment(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	if (type != MAGICK_TYPE_HYSH)
	{
		engagement->rounds++;
		return;
	}

	struct CAST_RESULT_T result;
	cast_test(engagement, 12, &result);
}
