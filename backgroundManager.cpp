#include "StdAfx.h"
#include "backgroundManager.h"
#include <fstream>
	
backgroundManager::backgroundManager(void)
{
	//General Vars
	level = 0; //Used to hold the current level
	clickLock = false;//Ensures no accidental double clicks
	playing = true; //Used for whole program loop
	inGame = false; //Used for loop when in game
	activeMenu = "start"; //Use to hold what menu is displayed
	reset = false; //Used to trigger game reset
	menuItem = 0; //Used to hold the menu item currently selected
	setMenuItem = false; //Used to set the default menu item
	optionChangeToggle = 'n'; //Stops accidental menu item changes
	//All used for scroll effect of death screen
	deadScreenScrollH = 0;
	deadScreenScrollY = 420;
	screen.h = 0;
	screen.w = 680;
	screen.x = 0;
	screen.y = 420;

	//Menu Setup
	//Menu Background
	menuBk.loadImage("Sprites/menuBK.png");
	//Menu Buttons
	menuImages[0][0].loadImage("Sprites/Menu/resume.png");
	menuImages[0][1].loadImage("Sprites/Menu/resumeHover.png");
	menuImages[1][0].loadImage("Sprites/Menu/newGame.png");
	menuImages[1][1].loadImage("Sprites/Menu/newGameHover.png");
	menuImages[2][0].loadImage("Sprites/Menu/exitGame.png");
	menuImages[2][1].loadImage("Sprites/Menu/exitGameHover.png");
	//Dead Menu Background
	deadScreenBk.loadImage("Sprites/deadScreen.png");
	//Start Screen Background
	startScreenBk.loadImage("Sprites/Menu/startScreen.jpg");
	//Story Lines
	storyScreenBk[0].loadImage("Sprites/Menu/levelOne.jpg");
	storyScreenBk[1].loadImage("Sprites/Menu/levelTwo.jpg");
	storyScreenBk[2].loadImage("Sprites/Menu/levelThree.jpg");
	storyScreenBk[3].loadImage("Sprites/Menu/wellDone.jpg");
}

backgroundManager::~backgroundManager(void)
{
}

void backgroundManager::mapSetup()
{
	//Setup Map
	//Level 0
	if(level == 0)
	{
		bkImage.loadImage("Sprites/Background1.jpg");
		leftBound = 25;
		rightBound = 655;
		groundLevel = 365;
		
		//Platforms
		platX[0] = 420;
		platY[0] = 340;

		platX[1] = 300;
		platY[1] = 280;

		platX[2] = 180;
		platY[2] = 340;

		platX[3] = 420;
		platY[3] = 220;

		platX[4] = 180;
		platY[4] = 220;
	}

	//Level 1
	if(level == 1)
	{
		bkImage.loadImage("Sprites/Background2.jpg");
		leftBound = 0;
		rightBound = bkImage.getWidth()-10;
		groundLevel = 365;
		
		//Platforms
		platX[0] = 80;
		platY[0] = 220;

		platX[1] = 360;
		platY[1] = 265;

		platX[2] = 360;
		platY[2] = 325;
		
		platX[3] = 500;
		platY[3] = 220;

		platX[4] = 220;
		platY[4] = 220;
	}

	//Level 2
	if(level == 2)
	{
		bkImage.loadImage("Sprites/Background3.jpg");
		leftBound = 0;
		rightBound = bkImage.getWidth()-30;
		groundLevel = 365;
		
		//Platforms
		platX[0] = 165;
		platY[0] = 200;

		platX[1] = 80;
		platY[1] = 260;

		platX[2] = 80;
		platY[2] = 320;
		
		platX[3] = 480;
		platY[3] = 250;

		platX[4] = 280;
		platY[4] = 250;
	}
}

void backgroundManager::levelAdvance()
{
	if(level <= 2)
	{
		++level;
		complete = true;
	}
}

void backgroundManager::draw(GWindow* Gwin)
{
	Gwin->drawImage(0,0,&bkImage);

	unsigned int i = 0;
	while(i<(sizeof(platX)/sizeof(int)))
	{
		gamePlatforms[i].drawPlatform(platX[i],platY[i],Gwin);
		++i;
	}
}

std::string backgroundManager::menuType()
{
	return activeMenu;
}

int backgroundManager::getGroundLevel()
{
	return groundLevel;
}

unsigned int backgroundManager::getPlatformQuant()
{
	return sizeof(platX)/sizeof(int);
}

int backgroundManager::platformX(unsigned int num)
{
	return gamePlatforms[num].getX();
}

int backgroundManager::platformY(unsigned int num)
{
	return gamePlatforms[num].getY();
}

int backgroundManager::platformWidth(unsigned int num)
{
	return gamePlatforms[num].getWidth();
}

int backgroundManager::platformHeight(unsigned int num)
{
	return gamePlatforms[num].getHeight();
}

int backgroundManager::getLeftBound()
{
	return leftBound;
}
int backgroundManager::getRightBound()
{
	return rightBound;
}
int backgroundManager::currentLevel()
{
	return level;
}

bool backgroundManager::isInGame()
{
	return inGame;
}

bool backgroundManager::isComplete()
{
	return complete;
}

void backgroundManager::pauseGame()
{
	inGame = false;
	activeMenu = "pause";
}

void backgroundManager::setStoryMenu()
{
	inGame = false;
	activeMenu = "story";
}
void backgroundManager::deadGuy()
{
	inGame = false;
	activeMenu = "dead";
}

void backgroundManager::pauseMenu(GWindow* Gwin)
{
	//Set Font Small & Gray
	Gwin->setPenColour(DARKRED);
	GFont bigFont("Arial",40);
	Gwin->setFont(&bigFont);

	//Menu Background
	Gwin->drawImageScaled(0,0,Gwin->getWidth()+5,Gwin->getHeight()+5,&menuBk);

	//Title
	Gwin->writeText(190,85,"GAME PAUSED!");

	//Menu Items Loop
	if(!setMenuItem)
	{
		menuItem = 0;
		setMenuItem = true;
	}
	unsigned int i = 0;
	while(i <= 2)
	{
		unsigned int j = 0;
		if(menuItem == i)
		{
			j = 1;
		}
		Gwin->drawImage(240,140+(i*60),&menuImages[i][j]);
		++i;
	}
}

void backgroundManager::startScreen(GWindow* Gwin)
{
	Gwin->drawImage(0,0,&startScreenBk);

	//Menu Items Loop
	if(!setMenuItem)
	{
		menuItem = 1;
		setMenuItem = true;
	}
	unsigned int i = 1;
	while(i <= 2)
	{
		unsigned int j = 0;
		if(menuItem == i)
		{
			j = 1;
		}
		Gwin->drawImage(240,120+(i*60),&menuImages[i][j]);
		++i;
	}
}

void backgroundManager::storyMenu(GWindow* Gwin, gameTime* gameTimer)
{
	Gwin->drawImage(0,0,&storyScreenBk[level]);

	//Menu Items Loop
	if(level == 3)
	{
		if(!setMenuItem)
		{
			std::ofstream highScores("highScores.txt",std::ios::app);

			highScores << "Score: " << gameTimer->getGameTime() << '\n';
			highScores.close();
			menuItem = 2;
			setMenuItem = true;
		}
	}
	else
	{
		if(!setMenuItem)
		{
			menuItem = 0;
			setMenuItem = true;
		}
	}
}

void backgroundManager::drawDeadScreen(GWindow* Gwin)
{
	//Set Font Small & Gray
	Gwin->setPenColour(BLACK);
	GFont bigFont("Arial",40);
	Gwin->setFont(&bigFont);

	//Dead Background
	if(deadScreenScrollH >= 420)
	{
		deadScreenScrollH = 420;
	}
	else
	{
		deadScreenScrollH = deadScreenScrollH + 10;
	}
	if(deadScreenScrollY <= 0)
	{
		deadScreenScrollY = 0;
	}
	else
	{
		deadScreenScrollY = deadScreenScrollY - 10;
	}
	screen.y = deadScreenScrollY;
	screen.h = deadScreenScrollH;
	Gwin->drawImageRect(0,0,&deadScreenBk,screen);

	//Title
	Gwin->writeText(190,85,"GAME OVER!");

	//Menu Items Loop
	if(!setMenuItem)
	{
		menuItem = 1;
		setMenuItem = true;
	}
	unsigned int i = 1;
	while(i <= 2)
	{
		unsigned int j = 0;
		if(menuItem == i)
		{
			j = 1;
		}
		Gwin->drawImage(240,120+(i*60),&menuImages[i][j]);
		++i;
	}
}


void backgroundManager::resetMenuToggle(char type)
{
	if(type == optionChangeToggle)
	{
		optionChangeToggle = 'n';
	}
}

void backgroundManager::menuClick()
{
	if(!clickLock)
	{
		switch(menuItem)
		{
		case 0:
			if(activeMenu == "story")
			{
				setStoryMenu();
				mapSetup();
				inGame = true;
				activeMenu = "none";
			}
			else
			{
				inGame = true;
				activeMenu = "none";
			}
			break;
		case 1:
			if(activeMenu == "start")
			{
				inGame = false;
				setStoryMenu();
			}
			else
			{
				level = 0;
				activeMenu = "none";
				inGame = true;
				reset = true;
			}
			break;
		case 2:
			//Exit Game
			playing = false;
			activeMenu = "none";
			break;
		}
		setMenuItem = false;
		clickLock = true;
	}
}

void backgroundManager::removeClickLock()
{
	clickLock = false;
}

bool backgroundManager::resetMap()
{
	return reset;
}

void backgroundManager::hasReset()
{
	reset = false;
}

bool backgroundManager::isPlaying()
{
	return playing;
}

void backgroundManager::changeMenu(std::string direction)
{
	if(optionChangeToggle == 'n')
	{
		if(direction == "down")
		{
			optionChangeToggle = 'd';
			++menuItem;
			if(activeMenu == "dead" || activeMenu == "start")
			{
				if(menuItem > 2)
				{
					menuItem = 1;
				}
			}
			if(activeMenu == "pause")
			{
				if(menuItem > 2)
				{
					menuItem = 0;
				}
			}
			if(activeMenu == "story")
			{
				if(level == 3)
				{
					if(menuItem > 2)
					{
						menuItem = 2;
					}
				}
				else
				{
					if(menuItem > 0)
					{
						menuItem = 0;
					}
				}
			}
		}
		else
		{
			optionChangeToggle = 'u';
			--menuItem;
			if(activeMenu == "dead" || activeMenu == "start")
			{
				if(menuItem < 1)
				{
					menuItem = 2;
				}
			}
			if(activeMenu == "pause")
			{
				if(menuItem < 0)
				{
					menuItem = 2;
				}
			}
			if(activeMenu == "story")
			{
				if(level == 3)
				{
					if(menuItem < 2)
					{
						menuItem = 2;
					}
				}
				else
				{
					if(menuItem < 0)
					{
						menuItem = 0;
					}
				}
			}
		}
	}
}