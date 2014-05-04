#pragma once

class uiManager
{
public:
	uiManager(void);
	~uiManager(void);
	
	void drawInterface(GWindow* Gwin, player* guy, std::string weaponName, std::string weaponInfo, gameTime* gameTimer, attack* currentAttack);
private:
	GImage heart[2];
	GImage weaponActive[3];
	GImage weaponInactive[3];
	GImage uiBackground;

	//Heart Animation
	double scale;
	int loop;
};
