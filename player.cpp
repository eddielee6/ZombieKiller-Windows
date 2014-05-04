#include "StdAfx.h"
#include "player.h"


player::player(void)
{
	isRight = true;
	jumping = false;
	isDown = false;
	inAir = true;
	attacked = false;
	attackLoop = 0;
	spriteState = 0;
	walkState = 0;
	health = 10;
	mana = 80;
	jumpHeight = 0;
	X = 50;
	Y = 200;
	speed = 8;

	//Load Sprites
	spriteR[0].loadImage("Sprites/Char_Stand-R_s01.png");
	spriteR[1].loadImage("Sprites/Char_Stand-R_s02.png");
	spriteR[2].loadImage("Sprites/Char_Stand-R_s03.png");
	spriteL[0].loadImage("Sprites/Char_Stand-L_s01.png");
	spriteL[1].loadImage("Sprites/Char_Stand-L_s02.png");
	spriteL[2].loadImage("Sprites/Char_Stand-L_s03.png");
	spriteJump[0].loadImage("Sprites/Char_Jump_R.png");
	spriteJump[1].loadImage("Sprites/Char_Jump_L.png");
	spriteDown[0].loadImage("Sprites/Char_Down_R.png");
	spriteDown[1].loadImage("Sprites/Char_Down_L.png");
	spriteWalkL[0].loadImage("Sprites/Char_Walk_L_s01.png");
	spriteWalkL[1].loadImage("Sprites/Char_Walk_L_s02.png");
	spriteWalkL[2].loadImage("Sprites/Char_Walk_L_s03.png");
	spriteWalkL[3].loadImage("Sprites/Char_Walk_L_s04.png");
	spriteWalkL[4].loadImage("Sprites/Char_Walk_L_s05.png");
	spriteWalkL[5].loadImage("Sprites/Char_Walk_L_s06.png");
	spriteWalkL[6].loadImage("Sprites/Char_Walk_L_s07.png");
	spriteWalkL[7].loadImage("Sprites/Char_Walk_L_s08.png");
	spriteWalkR[0].loadImage("Sprites/Char_Walk_R_s01.png");
	spriteWalkR[1].loadImage("Sprites/Char_Walk_R_s02.png");
	spriteWalkR[2].loadImage("Sprites/Char_Walk_R_s03.png");
	spriteWalkR[3].loadImage("Sprites/Char_Walk_R_s04.png");
	spriteWalkR[4].loadImage("Sprites/Char_Walk_R_s05.png");
	spriteWalkR[5].loadImage("Sprites/Char_Walk_R_s06.png");
	spriteWalkR[6].loadImage("Sprites/Char_Walk_R_s07.png");
	spriteWalkR[7].loadImage("Sprites/Char_Walk_R_s08.png");

	dead[0].loadImage("Sprites/Char_Dead_R.png");
	dead[1].loadImage("Sprites/Char_Dead_L.png");
}

player::~player(void)
{

}

void player::resetHealth()
{
	health = 10;
}

void player::isAttacked()
{
	if(!attacked)
	{
		attacked = true;
		--health;
		if(health > 0)
		{
			jump();
		}
	}
}

bool player::isAlive()
{
	if(health > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int player::getHealth()
{
	return health;
}

int player::getMana()
{
	return mana;
}

char player::getDir()
{
	if(isRight)
	{
		return 'r';
	}
	return 'l';
}

void player::drawPlayer(GWindow* Gwin)
{
	++spriteState;
	++walkState;
	if(spriteState == 3)
	{
		spriteState = 0;
	}
	if(walkState == 8)
	{
		walkState = 0;
	}

	if(isRight)
	{
		if(health > 0)
		{
			if(inAir)
			{
				Gwin->drawImage(X,Y,&spriteJump[0]);
			}
			else if(isDown)
			{
				Gwin->drawImage(X,Y,&spriteDown[0]);
			}
			else if(walking)
			{
				Gwin->drawImage(X,Y,&spriteWalkR[walkState]);
			}
			else if(attacked)
			{
				Gwin->drawImage(X,Y,&spriteJump[0]);
			}
			else
			{
				Gwin->drawImage(X,Y,&spriteR[spriteState]);
			}
		}
		else
		{
			Gwin->drawImage(X,Y+23,&dead[0]);
		}
	}
	else
	{
		if(health > 0 )
		{
			if(inAir)
			{
				Gwin->drawImage(X,Y,&spriteJump[1]);
			}
			else if(isDown)
			{
				Gwin->drawImage(X,Y,&spriteDown[1]);
			}
			else if(walking)
			{
				Gwin->drawImage(X,Y,&spriteWalkL[walkState]);
			}
			else if(attacked)
			{
				Gwin->drawImage(X,Y,&spriteJump[1]);
			}
			else
			{
				Gwin->drawImage(X,Y,&spriteL[spriteState]);
			}
		}
		else
		{
			Gwin->drawImage(X,Y+23,&dead[1]);
		}
	}
}

void player::faceRight(bool state)
{
	if(!attacked)
	{
		isRight = state;
	}
}

int player::getX()
{
	return X;
}

int player::getY()
{
	return Y;
}

void player::moveY(char type)
{
	switch(type)
	{
	case 'g':
		Y = Y + 1;
		break;
	case 'j':
		Y = Y - (speed*3);
		break;
	case 'e':
		Y = Y - speed;
		break;
	}
}

void player::moveX(char type)
{
	if(!isDown)
	{
		if(!attacked)
		{
			if(type == 'r')
			{
				X = X + speed;
			}
			if(type == 'l')
			{
				X = X - speed;
			}
		}
	}
}

bool player::jump()
{
	if(health > 0)
	{
		if(!inAir)
		{
			if(!jumping)
			{
				jumping = true;
				inAir = true;
			}
		}
		if(jumping)
		{
			++jumpHeight;

			if(jumpHeight < 4)
			{
				moveY('j'); //at start of jump faster for acceleration
			}
			else
			{
				moveY('e');//Slower at end of jump 'e' stands for end of jump
			}
			
			if(jumpHeight >= 6)
			{
				jumping = false;
				jumpHeight = 0;
				return true;
			}
		}
	}
	return false;
}

bool player::getJumpStatus()
{
	return jumping;
}

void player::endJump()
{
	inAir = false;
}

void player::down(bool state)
{
	if(!attacked)
	{
		isDown = state;
	}
}

void player::moving(char direction)
{
	if(!attacked)
	{
		walking = true;
		moveX(direction);
	}
}
void player::stopWalking()
{
	walking = false;
}

void player::freeFall()
{
	if(!attacked)
	{
		inAir = true;
	}
}

void player::gainedHealth()
{
	++health;
}

void player::lostMana(int amount)
{
	mana = mana - amount;
}
void player::gainedMana(int amount)
{
	mana = mana + amount;
}

void player::gravity(backgroundManager* bkground)
{
	unsigned int i = 0;
	bool onPlatform = false;
	bool fall = false;

	//Check if on a platform
	while(i < bkground->getPlatformQuant())
	{
		if((X+10 >= bkground->platformX(i) && X+10 <= bkground->platformWidth(i)+bkground->platformX(i))&&(Y+44 >= bkground->platformY(i) && Y+44 <= ( bkground->platformHeight(i)/2)+bkground->platformY(i)))
		{
			endJump();
			onPlatform = true;
		}
		++i;
	}

	//Apply Gravity
	if(Y < bkground->getGroundLevel())
	{
		if(!onPlatform)
		{
			fall = true;
		}
	}
	if(fall)
	{
		freeFall();
		moveY('g');
	}
	else
	{
		endJump();
		attacked = false;
	}
}

bool player::checkDown()
{
	return isDown;
}

void player::respawn()
{
	isRight = true;
	jumping = false;
	isDown = false;
	inAir = true;
	attacked = false;
	attackLoop = 0;
	spriteState = 0;
	walkState = 0;
	mana = 80;
	jumpHeight = 0;
	X = 50;
	Y = 200;
}