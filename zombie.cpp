#include "StdAfx.h"
#include "zombie.h"

zombie::zombie(void)
{
	speed = 3;
	falling = false;
	sprite[0][0].loadImage("Sprites/zombie_R_s01.png");
	sprite[0][1].loadImage("Sprites/zombie_R_s02.png");
	sprite[1][0].loadImage("Sprites/zombie_L_s01.png");
	sprite[1][1].loadImage("Sprites/zombie_L_s02.png");
	dead[0].loadImage("Sprites/deadZombie_R.png");
	dead[1].loadImage("Sprites/deadZombie_L.png");

	animateState = 0;
}

zombie::~zombie(void)
{
}

void zombie::setup(int x, int y, char dir, int minX, int maxX, int newHealth, bool spawn)
{
	posx = x;
	posy = y;
	minPos = minX;
	maxPos = maxX;
	direction = dir;
	health = newHealth;
	alive = spawn;
}

signed int zombie::getX()
{
	return posx;
}
signed int zombie::getY()
{
	return posy;
}
signed int zombie::getHealth()
{
	return health;
}

bool zombie::isAlive()
{
	return alive;
}

void zombie::fall()
{
	posy = posy + speed+2;
}

void zombie::animate()
{
	if(alive)
	{
		//Walking
		if(!falling)
		{
			if(direction == 'r')
			{
				if(posx < maxPos)
				{
					posx = posx + speed;
				}
				else
				{
					direction = 'l';
				}
			}
			else
			{
				if(posx > minPos)
				{
					posx = posx - speed;
				}
				else
				{
					direction = 'r';
				}
			}
		}
	}
}

void zombie::draw(GWindow* Gwin)
{
	unsigned int dir = 0;
	if(direction == 'l')
	{
		dir = 1;
	}
	if(alive)
	{
		unsigned int drawState = 0;
		if(animateState <2)
		{
			drawState = 1;
		}
		//Draw
		Gwin->drawImage(posx,posy,&sprite[dir][drawState]);

		//Health Bar
		Gwin->setPenColour(BLACK);
		Gwin->rectangle(posx-5,posy-10,(posx-5)+32,posy-5);
		if(health >= 7)
		{
			Gwin->setPenColour(GREEN);
		}
		if(health <= 6)
		{
			Gwin->setPenColour(ORANGE);
		}
		if(health <= 3)
		{
			Gwin->setPenColour(RED);
		}

		if(health < 0)
		{
			health = 0;
		}

		Gwin->rectangle(posx-4,posy-9,(posx-4)+(health*3),posy-6);

		//Next Animate Sequence
		++animateState;
		if(animateState > 4)
		{
			animateState = 0;
		}
	}
	else
	{
		Gwin->drawImage(posx,posy+24,&dead[dir]);
	}
}

void zombie::setFalling(bool fall)
{
	falling = fall;
}

void zombie::attacked(int damage, signed int dirX, bool melee)
{
	health = health - damage;
	if(posx >= dirX)
	{
		direction = 'l';
	}
	else
	{
		direction = 'r';
	}
	if(health <= 0)
	{
		alive = false;
	}
}