#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "baddies.h"

void init_crypt_ghoul(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	character->race = RACE_OTHER;

	strcpy(character->name, "Crypt Ghoul");

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 30;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 0;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 35;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 30;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 30;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 35;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 25;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 20;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 20;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 5;

	character->beast_wounds = 11;
}

void init_scaven(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	character->race = RACE_OTHER;

	strcpy(character->name, "Scaven");

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 30;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 30;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 30;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 30;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 40;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 35;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 30;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 30;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 20;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 20;

	character->beast_wounds = 11;
}

void init_varghulf(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	character->race = RACE_OTHER;

	strcpy(character->name, "Varghulf");

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 55;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 0;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 55;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 55;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 30;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 50;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 20;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 10;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 60;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 0;

	character->traits[TRAIT_UNDEAD] = 1;

	character->beast_wounds = 42;
	character->ap_mundane = 1;
}

void init_bloodletter_of_khorne(struct CHARACTER_T * character)
{
	memset((char*)character, 0, sizeof(struct CHARACTER_T));

	character->race = RACE_OTHER;

	strcpy(character->name, "Bloodletter of Khorne");

	character->characteristic_starting[CHARACTERISTIC_WEAPONS_SKILL] = 55;
	character->characteristic_starting[CHARACTERISTIC_BALLISTIC_SKILL] = 35;
	character->characteristic_starting[CHARACTERISTIC_STRENGTH] = 45;
	character->characteristic_starting[CHARACTERISTIC_TOUGHNESS] = 35;
	character->characteristic_starting[CHARACTERISTIC_INITIATIVE] = 60;
	character->characteristic_starting[CHARACTERISTIC_AGILITY] = 40;
	character->characteristic_starting[CHARACTERISTIC_DEXTERITY] = 30;
	character->characteristic_starting[CHARACTERISTIC_INTELLIGENCE] = 25;
	character->characteristic_starting[CHARACTERISTIC_WILLPOWER] = 70;
	character->characteristic_starting[CHARACTERISTIC_FELLOWSHIP] = 20;

	character->traits[TRAIT_DEMONIC] = 8;

	character->beast_wounds = 17;
	character->ap_mundane = 5;
}


