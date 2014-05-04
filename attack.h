#pragma once

class attack
{
public:
	attack(void);
	~attack(void);

	bool nowAttacking();
	bool isFireball();
	int nextAttackIn(gameTime* gameTimer);
	void animate(GWindow* Gwin, player* guy, weapons* weapon, gameTime* gameTimer);
	void setAttack(weapons* weapon, player* guy, gameTime* gameTimer);
	signed int getFireballX();
	signed int getFireballY();
	void stopFireball();
	char getMelee();

private:
	unsigned int type;
	char melee;
	unsigned int attackAgainAt;
	bool isAttacking;
	unsigned int attackStage;
	signed int fireballX, fireballY;
	bool newFireball;
	char fireballDir;
};
