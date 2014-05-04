//Includes
#include "stdafx.h"

//Global Classes
GWindow *Gwin;
player *guy;
backgroundManager *bkground;
weapons *weapon;
uiManager *ui;
gameTime *gameTimer;
attack *currentAttack;
enemyManager *badGuys;

//Main Functions
void gravity();
bool checkBounds(char dir);

//Time functions
unsigned int loop = 0;

int main()
{
	//Initilise Global Classes
	GWindow gameWindow(678,418,false);
	Gwin = &gameWindow;

	player mainPlayer;
	guy = &mainPlayer;

	backgroundManager gameBkground;
	bkground = &gameBkground;

	uiManager gameManager;
	ui = &gameManager;

	weapons gameWeapon;
	weapon = &gameWeapon;

	gameTime magicGameTimer;
	gameTimer = &magicGameTimer;

	attack goAttack;
	currentAttack = &goAttack;

	enemyManager enemyManagment(bkground);
	badGuys = &enemyManagment;

	badGuys->setup(bkground);
	bkground->mapSetup();

	//Game Loop
	while(bkground->isPlaying())
	{
		if(bkground->resetMap())
		{
			guy->respawn();
			guy->resetHealth();
			badGuys->setup(bkground);
			badGuys->setBossFight(false);
			bkground->mapSetup();
			bkground->hasReset();
		}

		if(bkground->isInGame())
		{
			//Escape To Pause
			if(Keyboard.isPressed(GwinKeyNames::ESCAPE))
			{
				bkground->pauseGame();
			}

			//Game Timer
			if(++loop >= 20) //Loop is Gsleep 50, Gsleep 1000 == 1 second, loops 20 time per second
			{
				loop = 0;
				gameTimer->increaseTime();
			}


			//-----------------Controles------------------
			//Tab to change weapon
			if(Keyboard.isPressed(GwinKeyNames::TAB))
			{
				weapon->changeWeapon("next"); //Cycles throught current weapon
			}
			if(!Keyboard.isPressed(GwinKeyNames::TAB))
			{
				weapon->changeWeapon("reset"); //Reset weapon wait
			}

			//Directional Controles
			if(!(Keyboard.isPressed(GwinKeyNames::CURSOR_LEFT))||!(Keyboard.isPressed(GwinKeyNames::CURSOR_RIGHT)))
			{
				if(Keyboard.isPressed(GwinKeyNames::CURSOR_LEFT))
				{
					if(checkBounds('l'))
					{
						guy->moving('l');
					}
					guy->faceRight(false);
				}
				if(Keyboard.isPressed(GwinKeyNames::CURSOR_RIGHT))
				{
					if(checkBounds('r'))
					{
						guy->moving('r');
					}
					guy->faceRight(true);
				}
			}
			
			//Space to Jump
			if(guy->getJumpStatus() == false) //Prevents calling jump twice is key is held down for longer than Gsleep(100)
			{
				if(Keyboard.isPressed(GwinKeyNames::SPACE))
				{
					guy->jump();
				}
			}

			//Return to attack
			if(Keyboard.isPressed('z'))
			{
				currentAttack->setAttack(weapon, guy, gameTimer);
			}

			//Arrow Key Down to crouch
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_DOWN))
			{
				guy->down(true);
			}
			else
			{
				guy->down(false);
			}

			//Clear screen
			Gwin->clear();

			//----------Check for animation loops------------

			if(!guy->isAlive())
			{
				bkground->deadGuy();
			}
			badGuys->animate(bkground); //Runs animation loop for zombies
			badGuys->detectAttacks(guy,currentAttack,weapon); //Checks for attacks to and from zombies
			badGuys->allDead(bkground,guy); //Checks if all zombies are dead

			//Check jump status
			if(guy->getJumpStatus() == true) //To create motion jump is recalled from the main game loop untill the jump siquence is finished
			{
				guy->jump();
			}
			else //if jump is not in effect normal gravity applys
			{
				int i = 0;
				while(i < 10)
				{
					guy->gravity(bkground);
					++i;
				}
			}
		}

		//--------DRAW GAME---------
		//Background
		bkground->draw(Gwin);
		//Bad Guys
		badGuys->draw(Gwin);
		//Draw Attack
		if(currentAttack->nowAttacking() || currentAttack->isFireball()) //Attack motion is held in a loop.. called over a number of frames
		{
			currentAttack->animate(Gwin,guy,weapon,gameTimer);
		}
		//Player
		guy->drawPlayer(Gwin);
		//Reset Walking Motion
		guy->stopWalking(); //Ensures walking motion is only drawn when arrow keys are held down not just pressed
		//Check if menu should be drawn
		if(!bkground->isInGame())
		{
			//Menu Controles
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_UP))
			{
				bkground->changeMenu("up");
			}
			if(!Keyboard.isPressed(GwinKeyNames::CURSOR_UP))
			{
				bkground->resetMenuToggle('u');
			}
			if(Keyboard.isPressed(GwinKeyNames::CURSOR_DOWN))
			{
				bkground->changeMenu("down");
			}
			if(!Keyboard.isPressed(GwinKeyNames::CURSOR_DOWN))
			{
				bkground->resetMenuToggle('d');
			}
			//Pressed Enter
			if(Keyboard.isPressed(GwinKeyNames::RETURN))
			{
				bkground->menuClick();
			}
			if(!Keyboard.isPressed(GwinKeyNames::RETURN))
			{
				bkground->removeClickLock();
			}
			//Menu Type
			if(bkground->menuType() == "pause")
			{
				bkground->pauseMenu(Gwin);
			}
			if(bkground->menuType() == "dead")
			{
				bkground->drawDeadScreen(Gwin);
			}
			if(bkground->menuType() == "story")
			{
				bkground->storyMenu(Gwin, gameTimer);
			}
			if(bkground->menuType() == "start")
			{
				bkground->startScreen(Gwin);
			}
		}

		//Draw Interface
		ui->drawInterface(Gwin,guy,weapon->getWeaponName(),weapon->getWeaponInfo(),gameTimer,currentAttack);

		//Refresh Game
		Gwin->refresh();
		Gsleep(50);
	}
	return 0;
}

bool checkBounds(char dir)
{
	if(dir == 'l')
	{
		if(guy->getX() > bkground->getLeftBound())
		{
			return true;
		}
	}
	if(dir == 'r')
	{
		if(guy->getX() < bkground->getRightBound())
		{
			return true;
		}
	}
	return false;
}