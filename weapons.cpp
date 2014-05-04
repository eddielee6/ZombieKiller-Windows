#include "StdAfx.h"
#include "weapons.h"

weapons::weapons(void)
{
	//Setup Dagger
	//Name
	weaponNames[0] = "Dagger";
	//Info
	weaponInfo[0] = "A fast but low damage weapon";
	//Damage
	weaponDamage[0] = 2;
	//Speed
	speed[0] = 0; //Lower speed faster attack, 0 for no delay
	//Mana Cost
	manaCost[0] = 0;
	//Ranged
	ranged[0] = false;
	//Images
	weaponImages[0][0].loadImage("Sprites/Dagger_R.png");
	weaponImages[0][1].loadImage("Sprites/Dagger_L.png");

	//Setup Battle Axe
	//Name
	weaponNames[1] = "Battle Axe";
	//Info
	weaponInfo[1] = "A very powerful yet slow weapon";
	//Damage
	weaponDamage[1] = 4;
	//Speed
	speed[1] = 1; //Lower speed faster attack, 0 for no delay
	//Mana Cost
	manaCost[1] = 0;
	//Ranged
	ranged[1] = false;
	//Images
	weaponImages[1][0].loadImage("Sprites/Axe_R.png");
	weaponImages[1][1].loadImage("Sprites/Axe_L.png");

	//Setup Fire Ball
	//Name
	weaponNames[2] = "Fire Ball";
	//Info
	weaponInfo[2] = "A ranged attack consuming mana";
	//Damage
	weaponDamage[2] = 4;
	//Speed
	speed[2] = 0; //Lower speed faster attack, 0 for no delay
	//Mana Cost
	manaCost[2] = 10;
	//Ranged
	ranged[2] = true;
	//Images
	weaponImages[2][0].loadImage("Sprites/fireball_R.png");
	weaponImages[2][1].loadImage("Sprites/fireball_L.png");
	
	//General Weapon Settings
	equiped = 0;
	changed = false;
}

weapons::~weapons(void)
{
}

GImage *weapons::getWeaponImage(int weapon, char direction)
{
	if(weapon == -1)
	{
		weapon = equiped;
	}
	if(direction == 'r')
	{
		return &weaponImages[weapon][0];
	}
	if(direction == 'l')
	{
		return &weaponImages[weapon][1];
	}
	return &weaponImages[weapon][0];
}

std::string weapons::getWeaponName()
{
	return weaponNames[equiped];
}

std::string weapons::getWeaponInfo()
{
	return weaponInfo[equiped];
}

unsigned int weapons::getWeaponDamage()
{
	return weaponDamage[equiped];
}

unsigned int weapons::getWeaponDamage(std::string weaponType)
{
	if(weaponType == "fireball")
	{
		return weaponDamage[2];
	}
	return weaponDamage[equiped];
}

unsigned int weapons::getSpeed()
{
	return speed[equiped];
}

signed int weapons::getManaCost()
{
	return manaCost[equiped];
}

bool weapons::isRanged()
{
	return ranged[equiped];
}

void weapons::changeWeapon(std::string type)
{
	if(type == "next")
	{
		if(!changed)
		{
			++equiped;
			if(equiped == 3)
			{
				equiped = 0;
			}
			changed = true;
		}
	}
	else
	{
		changed = false;
	}
}