#ifndef MAGICK_H
#define MAGICK_H
#include "core.h"

enum MAGICK_TYPE_T {
	MAGICK_TYPE_ULGU,
	MAGICK_TYPE_AQSHY,
	MAGICK_TYPE_HYSH,
	MAGICK_TYPE_SHYSH,
	MAGICK_TYPE_GHUR,
	MAGICK_TYPE_AZYR,
	MAGICK_TYPE_CHAMON,
	MAGICK_TYPE_GHYRAN,
	MAGICK_TYPE_NUM_TYPES
};

extern char* MAGICK_TYPE_T_NAMES[MAGICK_TYPE_NUM_TYPES];


typedef void (*CAST_FUNC_T)(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);

struct CAST_RESULT_T {
	char is_success;
	char is_critical;
	int sl;
	int cn;
	int overcasts;
};

void cast_test(struct ENGAGEMENT_T * engagement, int cn, struct CAST_RESULT_T * result);
void channel(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void channel_to_sl(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type, int sl_target);

void explore_spell(CAST_FUNC_T spell, char* name, struct ENGAGEMENT_T * engagement_orig, enum MAGICK_TYPE_T type);

void cast_dart(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_blast(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_bolt(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_chain_attack(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_shadow_dagger(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_shadow_dagger_w_followup(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_shadow_dagger_v2(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_great_fires_of_uzhul(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_banishment(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);

#endif
