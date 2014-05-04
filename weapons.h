#pragma once

class weapons
{
public:
	weapons(void);
	~weapons(void);

	std::string getWeaponName();
	std::string weapons::getWeaponInfo();
	unsigned int getWeaponDamage();
	unsigned int getWeaponDamage(std::string weaponDammage);
	unsigned int getSpeed();
	signed int getManaCost();
	bool isRanged();
	GImage *getWeaponImage(int weapon, char direction);
	
	void changeWeapon(std::string type);

private:
	//Weapon Attributes
	std::string weaponNames[3];
	std::string weaponInfo[3];
	unsigned int weaponDamage[3];
	unsigned int speed[3];
	unsigned int manaCost[3];
	bool ranged[3];
	GImage weaponImages[3][2];
	
	//General Veriables
	bool changed;
	unsigned int equiped;
};
