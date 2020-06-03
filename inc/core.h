#ifndef CORE_H
#define CORE_H


enum SKILL_T {
	SKILL_LANGUAGE_MAGICK,
	SKILL_CHANNELING_ULGU,
	SKILL_CHANNELING_AQSHY,
	SKILL_CHANNELING_HISH,
	SKILL_CHANNELING_SHYISH,
	SKILL_CHANNELING_GHUR,
	SKILL_CHANNELING_AZYR,
	SKILL_CHANNELING_CHAMON,
	SKILL_CHANNELING_GHYRAN,
	SKILL_NUM_SKILLS
};

enum CHARACTERISTIC_T {
	CHARACTERISTIC_WEAPONS_SKILL,
	CHARACTERISTIC_BALLISTIC_SKILL,
	CHARACTERISTIC_STRENGTH,
	CHARACTERISTIC_TOUGHNESS,
	CHARACTERISTIC_INITIATIVE,
	CHARACTERISTIC_AGILITY,
	CHARACTERISTIC_DEXTERITY,
	CHARACTERISTIC_INTELLIGENCE,
	CHARACTERISTIC_WILLPOWER,
	CHARACTERISTIC_FELLOWSHIP,
	CHARACTERISTIC_NUM_CHARACTERISTICS
};

enum TALENT_T {
	TALENT_INSTINCTIVE_DICTION,
	TALENT_AETHYRIC_ATTUNEMENT,
	TALENT_LUCK,
	TALENT_PERFECT_PITCH,
	TALENT_NUM_TALENTS
};

enum RACE_T {
	RACE_ELF,
	RACE_HUMAN
};

struct CHARACTER_T {
	char name[100];
	enum RACE_T race;
	int characteristic_starting[CHARACTERISTIC_NUM_CHARACTERISTICS];
	int characteristic_advances[CHARACTERISTIC_NUM_CHARACTERISTICS];
	int skill_advances[SKILL_NUM_SKILLS];
	int talents[TALENT_NUM_TALENTS];
	int wounds_left;
	int fortune_points;
	int fate_points;
	int resolve_points;
	int resilience_points;

	int ap;
};

struct ENGAGEMENT_T {
	struct CHARACTER_T * aggressor;
	struct CHARACTER_T * defender;
	int num_defenders;
	int magick_bonus;
	int dispel_bonus_sl;

	int sl_channeled;

	int damage_applied;
	int minor_misscasts;
	int major_misscasts;

	int rounds;

	int total_cast_sls;
	int total_cast_overcasts;
	int total_cast_successes;
};

#define GET_CHARACTERISTIC(character, characteristic) (character->characteristic_starting[characteristic] + character->characteristic_advances[characteristic])
#define GET_SKILL(character, skill) (GET_CHARACTERISTIC(character, skill_to_char_map[skill]) + character->skill_advances[skill])

#define GET_CHARACTERISTIC_BONUS(character, characteristic) (GET_CHARACTERISTIC(character, characteristic)/10)
#define GET_SKILL_BONUS(character, skill) (GET_SKILL(character, skill)/10)

#define FAST_RAND_MAX 32767

int fast_rand(void);
int d(int sides);
void reset_character(struct CHARACTER_T * character);

enum CHARACTERISTIC_T skill_to_char_map [SKILL_NUM_SKILLS];

#endif
