#include "StdAfx.h"
#include "enemyManager.h"
#include "backgroundManager.h"

enemyManager::enemyManager(backgroundManager* bkground)
{
	bossFight = false;

}

enemyManager::~enemyManager(void)
{
}

void enemyManager::setBossFight(bool fight)
{
	bossFight = fight;
}

void enemyManager::setup(backgroundManager* bkground)
{
	if(bkground->currentLevel() == 0)
	{
		zombies[0].setup(130,300,'l',25,655,10,true);
		zombies[1].setup(230,100,'l',185,248,10,true);
		zombies[2].setup(330,100,'r',305,368,10,true);
		zombies[3].setup(430,200,'l',425,488,10,true);
		zombies[4].setup(520,250,'r',25,655,10,true);
	}
	if(bkground->currentLevel() == 1)
	{
		zombies[0].setup(100,150,'l',80,145,10,true);
		zombies[1].setup(230,150,'r',220,285,10,true);
		zombies[2].setup(370,200,'r',360,425,10,true);
		zombies[3].setup(370,250,'l',360,425,10,true);
		zombies[4].setup(420,350,'r',0,655,10,true);
	}
	if(bkground->currentLevel() == 2)
	{
		zombies[0].setup(100,150,'l',80,145,10,true);
		zombies[1].setup(300,150,'r',280,345,10,true);
		zombies[2].setup(500,200,'r',480,545,10,true);
		zombies[3].setup(500,250,'r',0,630,10,true);
		zombies[4].setup(600,350,'l',0,630,10,true);
	}
}

void enemyManager::allDead(backgroundManager* bkground, player* guy)
{
	if(bossFight)
	{
		if(!adolf.isAlive())
		{
			bkground->levelAdvance();
			bkground->setStoryMenu();
		}
	}
	unsigned int i = 0;
	int numDead = 0;
	while(i < sizeof(zombies)/sizeof(zombie))
	{
		if(!zombies[i].isAlive())
		{
			++numDead;
		}
		++i;
	}
	if(numDead >= sizeof(zombies)/sizeof(zombie))
	{
		
		if(bkground->currentLevel() == 2)
		{
			if(!bossFight)
			{
				adolf.setup(180,120,'r',0,630,100,true);
				bossFight = true;
			}
		}
		else
		{
			bkground->levelAdvance();
			setup(bkground);
			bkground->mapSetup();
			guy->respawn();
			bkground->setStoryMenu();
			bkground->hasReset();
		}
	}
}

void enemyManager::detectAttacks(player* guy, attack* currentAttack, weapons* weapon)
{
	//Zombie attacks you
	unsigned int i = 0;
	while(i < sizeof(zombies)/sizeof(zombie))
	{
		if(zombies[i].isAlive())
		{
			if((guy->getX()+12) >= zombies[i].getX() && (guy->getX()+12) <= (zombies[i].getX()+30) && (guy->getY()+22) >= zombies[i].getY() && (guy->getY()+22) <= (zombies[i].getY()+45))
			{
				guy->isAttacked();
			}
		}
		++i;
	}

	//Hitler Attacks You
	if(bossFight)
	{
		if(adolf.isAlive())
		{
			if((guy->getX()+12) >= adolf.getX() && (guy->getX()+12) <= (adolf.getX()+56) && (guy->getY()+22) >= adolf.getY() && (guy->getY()+22) <= (adolf.getY()+56))
			{
				guy->isAttacked();
			}
		}
	}

	//Fireball Attack
	if(currentAttack->isFireball())
	{
		if(bossFight)
		{
			if(adolf.isAlive())
			{
				if((currentAttack->getFireballX()+6) >= adolf.getX() && (currentAttack->getFireballX()+12) <= (adolf.getX()+56) && (currentAttack->getFireballY()+8) >= adolf.getY() && (currentAttack->getFireballY()+8) <= (adolf.getY()+56))
				{
					adolf.attacked(weapon->getWeaponDamage("fireball"),guy->getX(),false);
					currentAttack->stopFireball();
				}
			}
		}
		unsigned int j = 0;
		while(j < sizeof(zombies)/sizeof(zombie))
		{
			if(zombies[j].isAlive())
			{
				if((currentAttack->getFireballX()+6) >= zombies[j].getX() && (currentAttack->getFireballX()+12) <= (zombies[j].getX()+30) && (currentAttack->getFireballY()+8) >= zombies[j].getY() && (currentAttack->getFireballY()+8) <= (zombies[j].getY()+44))
				{
					zombies[j].attacked(weapon->getWeaponDamage("fireball"),guy->getX(),false);
					currentAttack->stopFireball();
				}
			}
			++j;
		}
	}

	//Dagger Attack
	
	if(currentAttack->getMelee() == 'd')
	{
		if(bossFight)
		{
			if(guy->getDir() == 'r')
			{
				if((guy->getX()+25) >= adolf.getX() && (guy->getX()+25) <= (adolf.getX()+56) && (guy->getY()+10) >= adolf.getY() && (guy->getY()+10) <= (adolf.getY()+56))
				{
					adolf.attacked(weapon->getWeaponDamage(),guy->getX(),true);
				}
			}
			else
			{
				if((guy->getX()-5) >= adolf.getX() && (guy->getX()-5) <= (adolf.getX()+56) && (guy->getY()+10) >= adolf.getY() && (guy->getY()+10) <= (adolf.getY()+56))
				{
					adolf.attacked(weapon->getWeaponDamage(),guy->getX(),true);
				}
			}
		}
		//Zombies
		unsigned int j = 0;
		while(j < sizeof(zombies)/sizeof(zombie))
		{
			if(zombies[j].isAlive())
			{
				if(guy->getDir() == 'r')
				{
					if((guy->getX()+25) >= zombies[j].getX() && (guy->getX()+25) <= (zombies[j].getX()+30) && (guy->getY()+10) >= zombies[j].getY() && (guy->getY()+10) <= (zombies[j].getY()+45))
					{
						zombies[j].attacked(weapon->getWeaponDamage(),guy->getX(),true);
					}
				}
				else
				{
					if((guy->getX()-5) >= zombies[j].getX() && (guy->getX()-5) <= (zombies[j].getX()+30) && (guy->getY()+10) >= zombies[j].getY() && (guy->getY()+10) <= (zombies[j].getY()+45))
					{
						zombies[j].attacked(weapon->getWeaponDamage(),guy->getX(),true);
					}
				}
			}
			++j;
		}
	}

	//Axe Attack
	if(currentAttack->getMelee() == 'a')
	{
		if(bossFight)
		{
			if(guy->getDir() == 'r')
			{
				if((guy->getX()+25) >= adolf.getX() && (guy->getX()+25) <= (adolf.getX()+56) && (guy->getY()+10) >= adolf.getY() && (guy->getY()+10) <= (adolf.getY()+56))
				{
					adolf.attacked(weapon->getWeaponDamage(),guy->getX(),true);
				}
			}
			else
			{
				if((guy->getX()-5) >= adolf.getX() && (guy->getX()-5) <= (adolf.getX()+56) && (guy->getY()+10) >= adolf.getY() && (guy->getY()+10) <= (adolf.getY()+56))
				{
					adolf.attacked(weapon->getWeaponDamage(),guy->getX(),true);
				}
			}
		}
		unsigned int j = 0;
		while(j < sizeof(zombies)/sizeof(zombie))
		{
			if(zombies[j].isAlive())
			{
				if(guy->getDir() == 'r')
				{
					if((guy->getX()+25) >= zombies[j].getX() && (guy->getX()+25) <= (zombies[j].getX()+30) && (guy->getY()+10) >= zombies[j].getY() && (guy->getY()+10) <= (zombies[j].getY()+45))
					{
						zombies[j].attacked(weapon->getWeaponDamage(),guy->getX(),true);
					}
				}
				else
				{
					if((guy->getX()-5) >= zombies[j].getX() && (guy->getX()-5) <= (zombies[j].getX()+30) && (guy->getY()+10) >= zombies[j].getY() && (guy->getY()+10) <= (zombies[j].getY()+45))
					{
						zombies[j].attacked(weapon->getWeaponDamage(),guy->getX(),true);
					}
				}
			}
			++j;
		}
	}
}

void enemyManager::animate(backgroundManager* bkground)
{
	gravity(bkground);
	unsigned int i = 0;
	while(i < sizeof(zombies)/sizeof(zombie))
	{
		zombies[i].animate();
		++i;
	}
	if(bossFight)
	{
		adolf.animate();
	}
}

void enemyManager::draw(GWindow* Gwin)
{
	unsigned int i = 0;
	while(i < sizeof(zombies)/sizeof(zombie))
	{
		zombies[i].draw(Gwin);
		++i;
	}
	if(bossFight)
	{
		adolf.draw(Gwin);
	}
}

void enemyManager::gravity(backgroundManager* bkground)
{
	unsigned int z = 0;
	unsigned int i = 0;
	bool falling = false;
	bool onPlatform = false;
	while(z < sizeof(zombies)/sizeof(zombie))
	{
		//Check if is on platform
		i = 0;
		onPlatform = false;
		while(i < bkground->getPlatformQuant())
		{
			if((zombies[z].getX()+15 >= bkground->platformX(i) && zombies[z].getX()+15 <= bkground->platformWidth(i)+bkground->platformX(i))&&(zombies[z].getY()+44 >= bkground->platformY(i) && zombies[z].getY()+44 <= ( bkground->platformHeight(i)/2)+bkground->platformY(i)))
			{
				onPlatform = true;
			}
			++i;
		}

		//Apply Gravity
		if(zombies[z].getY() < bkground->getGroundLevel())
		{
			if(!onPlatform)
			{
				zombies[z].fall();
				falling = true;
			}
			else
			{
				falling = false;
			}
		}
		else
		{
			falling = false;
		}
		zombies[z].setFalling(falling);
		++z;
	}

	//For Hitler
	if(bossFight)
	{
		i = 0;
		onPlatform = false;
		falling = false;

		//Check if on a platform
		while(i < bkground->getPlatformQuant())
		{
			if((adolf.getX()+20 >= bkground->platformX(i) && adolf.getX()+20 <= bkground->platformWidth(i)+bkground->platformX(i))&&(adolf.getY()+56 >= bkground->platformY(i) && adolf.getY()+56 <= ( bkground->platformHeight(i)/2)+bkground->platformY(i)))
			{
				onPlatform = true;
			}
			++i;
		}

		//Apply Gravity
		if(adolf.getY()+11 < bkground->getGroundLevel())
		{
			if(!onPlatform)
			{
				falling = true;
			}
		}
		if(falling)
		{
			adolf.fall();
		}
		else
		{
			falling = false;
		}
		adolf.setFalling(falling);
	}
}