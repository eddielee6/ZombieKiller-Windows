#include "StdAfx.h"
#include "attack.h"

attack::attack(void)
{
	isAttacking = false;
	melee = 'n';
	attackAgainAt = 0;
	type = 0;
	attackStage = 0;
	fireballX = 0;
	fireballY = 0;
	newFireball = true;
	fireballDir = 'r';
}

attack::~attack(void)
{
}

bool attack::isFireball()
{
	return !newFireball;
}

signed int attack::getFireballX()
{
	return fireballX;
}

signed int attack::getFireballY()
{
	return fireballY;
}

void attack::setAttack(weapons* weapon, player* guy, gameTime* gameTimer)
{
	if(!guy->checkDown())
	{
		//If count down has reset
		if(gameTimer->getElapsedTime() >= attackAgainAt)
		{
			//If is enough mana
			if(guy->getMana() >= weapon->getManaCost())
			{
				//Set Flag
				bool canAttack = true;

				//Set weapon
				std::string name = weapon->getWeaponName();
				if(name == "Dagger")
				{
					type = 0;
					melee = 'd';
				}
				else if(name == "Battle Axe")
				{
					type = 1;
					melee = 'a';
				}
				else if(name == "Fire Ball")
				{
					type = 2;
				}
				if(type == 2)
				{
					if(!newFireball)
					{
						canAttack = false;
					}
				}
				if(canAttack)
				{
					//Reduce mana
					guy->lostMana(weapon->getManaCost());
					//Set attack count down if applicable
					attackAgainAt = gameTimer->getElapsedTime() + weapon->getSpeed();
					//Set attack status
					isAttacking = true;
				}
			}
		}
	}
}


void attack::animate(GWindow* Gwin, player* guy, weapons* weapon, gameTime* gameTimer)
{
	int xGuy = guy->getX();
	int yGuy = guy->getY();

	//Dagger
	if(type == 0)
	{
		if(attackStage < 4)
		{
			if(!guy->checkDown())
			{
				if(guy->getDir() == 'r')
				{
					Gwin->drawImageScaledRotated(xGuy+5,yGuy+2,32,32,weapon->getWeaponImage(0,'r'),360-(attackStage*20));
				}
				else
				{
					Gwin->drawImageScaledRotated(xGuy-16,yGuy+2,32,32,weapon->getWeaponImage(0,'l'),0+(attackStage*20));
				}
			}
			++attackStage;
		}
		else
		{
			isAttacking = false;
			attackStage = 0;
			melee = 'n';
		}
	}

	//Axe
	if(type == 1)
	{
		if(!guy->checkDown())
		{
			if(guy->getDir() == 'r')
			{
				Gwin->drawImageScaledRotated(xGuy+5,yGuy+2,32,32,weapon->getWeaponImage(1,'r'),0+(attackStage*20));
			}
			else
			{
				Gwin->drawImageScaledRotated(xGuy-16,yGuy+2,32,32,weapon->getWeaponImage(1,'l'),360-(attackStage*20));
			}
		}
		if(attackStage < 4)
		{
			++attackStage;
		}

		if(gameTimer->getElapsedTime() >= attackAgainAt)
		{
			isAttacking = false;
			attackStage = 0;
			melee = 'n';
		}
	}

	//Fireball
	if(type == 2 || !newFireball)
	{
		if(newFireball)
		{
			if(guy->getDir() == 'r')
			{
				fireballDir = 'r';
				fireballX = xGuy + 20;
				fireballY = yGuy + 5;
			}
			else
			{
				fireballDir = 'l';
				fireballX = xGuy - 20;
				fireballY = yGuy + 5;
			}
			newFireball = false;
		}
		else
		{
			if(fireballDir == 'r')
			{
				if(fireballX < Gwin->getWidth())
				{
					fireballX = fireballX + 12;
				}
				else
				{
					stopFireball();
				}
			}
			else
			{
				if(fireballX > -16)
				{
					fireballX = fireballX - 12;
				}
				else
				{
					stopFireball();
				}
			}
		}
		Gwin->drawImage(fireballX,fireballY,weapon->getWeaponImage(2,fireballDir));
	}
	
}

void attack::stopFireball()
{
	newFireball = true;
	isAttacking = false;
}

char attack::getMelee()
{
	return melee;
}

int attack::nextAttackIn(gameTime* gameTimer)
{
	return attackAgainAt - gameTimer->getElapsedTime();
}

bool attack::nowAttacking()
{
	return isAttacking;
}
