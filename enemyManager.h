#pragma once
#include "zombie.h"
#include "hitler.h"

class enemyManager
{
public:
	enemyManager(backgroundManager* bkground);
	~enemyManager(void);

	void draw(GWindow* Gwin);
	void animate(backgroundManager* bkground);
	void detectAttacks(player* guy, attack* currentAttack, weapons* weapon);
	void setup(backgroundManager* bkground);
	void allDead(backgroundManager* bkground, player* guy);
	void setBossFight(bool fight);

private:
	zombie zombies[5];
	hitler adolf;
	bool bossFight;
	void enemyManager::gravity(backgroundManager* bkground);
};
