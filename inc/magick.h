#ifndef MAGICK_H
#define MAGICK_H

enum MAGICK_TYPE_T {
	MAGICK_TYPE_ULGU,
	MAGICK_TYPE_AQSHY,
	MAGICK_TYPE_NUM_TYPES
};

struct CAST_RESULT_T {
	char is_success;
	char is_critical;
	int sl;
	int cn;
	int overcasts;
};

void cast_test(struct ENGAGEMENT_T * engagement, int cn, struct CAST_RESULT_T * result);
void channel(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void channel_and_cast_test(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type, int cn, int channel_target, struct CAST_RESULT_T * result);

void cast_dart(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_blast(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_bolt(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_shadow_dagger(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_shadow_dagger_w_followup(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);
void cast_great_fires_of_uzhul(struct ENGAGEMENT_T * engagement, enum MAGICK_TYPE_T type);

#endif
