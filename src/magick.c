#include "core.h"
#include "magick.h"

enum SKILL_T magick_type_to_channel_skill[MAGICK_TYPE_NUM_TYPES] = {
		SKILL_CHANNELING_ULGU,
		SKILL_CHANNELING_AQSHY
};

void cast_test(struct ENGAGEMENT_T * engagement, int cn, struct CAST_RESULT_T * result)
{
	struct CHARACTER_T * caster = engagement->aggressor;
	int roll = d(100);
	int base = GET_SKILL(caster, SKILL_LANGUAGE_MAGICK);
	base += engagement->magick_bonus;
	int delta = base - roll;
	result->is_critical = ((roll%100)/10 == roll%10);

	result->cn = cn;
	result->is_success = 0;

	if (delta < 0 || roll > 95)
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
	if ((roll%100)/10 == roll%10)
	{
		// Critical channel
		if (delta > 0 && roll <= 95)
		{
			// Success
			engagement->sl_channeled = 100;
			if (caster->talents[TALENT_AETHYRIC_ATTUNEMENT] == 0)
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

		if (delta > 0 && roll <= 95)
		{
			engagement->sl_channeled += caster->talents[TALENT_AETHYRIC_ATTUNEMENT];
		}
	}

	if (engagement->sl_channeled < 0)
	{
		engagement->sl_channeled = 0;
	}

	engagement->rounds++;
}

void cast_dart(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CAST_RESULT_T result;
	cast_test(engagement, 0, &result);

	if (result.is_success)
	{
		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS) + engagement->defender->ap;
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl;
		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
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
		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS);
		if (type != MAGICK_TYPE_ULGU)
		{
			soak += engagement->defender->ap;
		}
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 3;
		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
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
		int soak = GET_CHARACTERISTIC_BONUS(engagement->defender, CHARACTERISTIC_TOUGHNESS);
		if (type != MAGICK_TYPE_ULGU)
		{
			soak += engagement->defender->ap;
		}
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 4;
		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
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

void cast_shadow_dagger(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
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
		if (type != MAGICK_TYPE_ULGU)
		{
			soak += engagement->defender->ap;
		}
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
		if (type != MAGICK_TYPE_ULGU)
		{
			soak += engagement->defender->ap;
		}
		int damage = GET_CHARACTERISTIC_BONUS(engagement->aggressor, CHARACTERISTIC_WILLPOWER)+result.sl + 2 + toughness_ignore;
		damage -= soak;
		if (damage <= 0)
		{
			damage = 1;
		}
		if (damage > 0)
		{
			int num_targets = 1;
			engagement->damage_applied += damage*num_targets + toughness_ignore + engagement->defender->ap;
		}
	}
}

void cast_great_fires_of_uzhul(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type)
{
	struct CAST_RESULT_T result;
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
