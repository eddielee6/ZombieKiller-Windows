#include "StdAfx.h"
#include "uiManager.h"
#include "math.h"


uiManager::uiManager(void)
{
	heart[0].loadImage("Sprites/heart.png");
	heart[1].loadImage("Sprites/deadHeart.png");

	weaponActive[0].loadImage("Sprites/ActiveDagger.png");
	weaponActive[1].loadImage("Sprites/activeAxe.png");
	weaponActive[2].loadImage("Sprites/activeFireball.png");

	weaponInactive[0].loadImage("Sprites/InactiveDagger.png");
	weaponInactive[1].loadImage("Sprites/InactiveAxe.png");
	weaponInactive[2].loadImage("Sprites/InactiveFireball.png");

	uiBackground.loadImage("Sprites/uiBar.png");

	//Heart Animation
	scale = 1.0;
	loop = 0;
}

uiManager::~uiManager(void)
{
}

void uiManager::drawInterface(GWindow* Gwin, player* guy, std::string weaponName, std::string weaponInfo, gameTime* gameTimer, attack* currentAttack)
{
	//Background
	Gwin->drawImage(0,0,&uiBackground);

	//Set Font Gold
	GFont uiFont("Arial",15);
	Gwin->setFont(&uiFont);
	Gwin->setPenColour(GOLD);

	//Write Heading
	Gwin->writeText(20,15,"Health");
	Gwin->writeText(20,35,"Mana");
	Gwin->writeText(265,20,"Weapon");
	Gwin->writeText(510,20,"Time");

	//Set Font Red
	Gwin->setPenColour(RED);

	//Weapon Info
	//Write Weapon Name
	Gwin->writeString(395,20,weaponName);

	//Assign Weapons With Number
	unsigned int weaponNumber = 0;
	if(weaponName == "Dagger")
	{
		weaponNumber = 0;
	}
	else if(weaponName == "Battle Axe")
	{
		weaponNumber = 1;
	}
	else if(weaponName == "Fire Ball")
	{
		weaponNumber = 2;
	}

	//Attack count down
	Gwin->setPenColour(GREEN);
	if(!currentAttack->isFireball())
	{
		if(currentAttack->nextAttackIn(gameTimer) <= 0)
		{
			Gwin->writeText(435,38,"Ready");
		}
		else
		{
			Gwin->writeText(435,38,"Wait:");
			Gwin->writeInt(473,38,currentAttack->nextAttackIn(gameTimer));
		}
	}
	else
	{
		Gwin->writeText(435,38,"Fired");
	}

	//Set Font Small & Gray
	Gwin->setPenColour(GRAY);
	GFont smallFont("Arial",10);
	Gwin->setFont(&smallFont);

	//Write Weapon Info
	Gwin->writeString(265,40,weaponInfo);

	//Draw Weapon Select Bar
	unsigned int k = 0;
	while(k < 3)
	{
		if(k == weaponNumber)
		{
			Gwin->drawImage(330+(20*k),20,&weaponActive[k]);
		}
		else
		{
			Gwin->drawImage(330+(20*k),20,&weaponInactive[k]);
		}
		++k;
	}

	//Set Font Small & Gray
	Gwin->setPenColour(GRAY);
	Gwin->setFont(&smallFont);

	//Write Time Info
	Gwin->writeText(510,40,"Faster time gets better score");

	//Set Font Normal & Red
	Gwin->setPenColour(RED);
	Gwin->setFont(&uiFont);


	Gwin->writeString(555,20,gameTimer->getGameTime());

	//Draw Hearts Health Bar
	signed int i = 1;
	while(i <= 10)
	{
		if(i <= guy->getHealth())
		{
			if(i == guy->getHealth())
			{
				int hHeight;
				int hWidth;
				int offSet;
				hHeight = ceil(10 * scale);
				hWidth = ceil(12* scale);
				offSet = ceil(hHeight - (10 * scale));
				if(loop == 2)
				{
					scale = scale + 0.1;
					if(scale >= 1.6)
					{
						scale = 1.0;
					}
					loop = 0;
				}
				else
				{
					++loop;
				}
				Gwin->drawImageScaled(72+((i*15)-15),20-offSet,hWidth,hHeight,&heart[0]);
			}
			else
			{
				Gwin->drawImage(72+((i*15)-15),20,&heart[0]);
			}
		}
		else
		{
			Gwin->drawImage(72+((i*15)-10),20,&heart[1]);
		}
		++i;
	}

	//Set Colour Blue
	Gwin->setPenColour(DEEPSKYBLUE);

	//Draw Mana Bar
	Gwin->rectangle(72,39,72+(guy->getMana()*2),49);
}