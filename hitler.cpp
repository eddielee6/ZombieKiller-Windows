#include "StdAfx.h"
#include "hitler.h"

hitler::hitler(void)
{
	speed = 3;
	falling = false;
	animateState = 0;
	nextFrame = false;

	sprite[0].loadImage("Sprites/hitler/hitler_s01.png");
	sprite[1].loadImage("Sprites/hitler/hitler_s02.png");
	sprite[2].loadImage("Sprites/hitler/hitler_s03.png");
	sprite[3].loadImage("Sprites/hitler/hitler_s04.png");
	sprite[4].loadImage("Sprites/hitler/hitler_s05.png");
	sprite[5].loadImage("Sprites/hitler/hitler_s06.png");
	sprite[6].loadImage("Sprites/hitler/hitler_s07.png");
	sprite[7].loadImage("Sprites/hitler/hitler_s08.png");
	sprite[8].loadImage("Sprites/hitler/hitler_s09.png");
	sprite[9].loadImage("Sprites/hitler/hitler_s10.png");
	sprite[10].loadImage("Sprites/hitler/hitler_s11.png");
	sprite[11].loadImage("Sprites/hitler/hitler_s12.png");
	sprite[12].loadImage("Sprites/hitler/hitler_s13.png");
	sprite[13].loadImage("Sprites/hitler/hitler_s14.png");
}

hitler::~hitler(void)
{
}

void hitler::setup(int x, int y, char dir, int minX, int maxX, int newHealth, bool spawn)
{
	posx = x;
	posy = y;
	minPos = minX;
	maxPos = maxX;
	direction = dir;
	health = newHealth;
	alive = spawn;
}

signed int hitler::getX()
{
	return posx;
}
signed int hitler::getY()
{
	return posy;
}
signed int hitler::getHealth()
{
	return health;
}

bool hitler::isAlive()
{
	return alive;
}

void hitler::fall()
{
	posy = posy + speed+2;
}

void hitler::animate()
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

void hitler::draw(GWindow* Gwin)
{
	//Draw
	Gwin->drawImage(posx,posy,&sprite[animateState]);

	//Health Bar
	Gwin->setPenColour(BLACK);
	Gwin->rectangle(posx-5,posy-10,(posx-5)+62,posy-5);
	if(health >= 70)
	{
		Gwin->setPenColour(GREEN);
	}
	if(health <= 69)
	{
		Gwin->setPenColour(ORANGE);
	}
	if(health <= 30)
	{
		Gwin->setPenColour(RED);
	}
	if(health <= 0)
	{
		health = 0;
	}

	Gwin->rectangle(posx-4,posy-9,(posx-4)+((health*3)/5),posy-6);

	//Next Animate Sequence
	if(nextFrame)
	{
		++animateState;
		if(animateState > 13)
		{
			animateState = 0;
		}
		nextFrame = false;
	}
	else
	{
		nextFrame = true;
	}
}

void hitler::setFalling(bool fall)
{
	falling = fall;
}

void hitler::attacked(int damage, signed int dirX, bool melee)
{
	if(health > damage)
	{
		health = health - damage;
	}
	else
	{
		alive = false;
	}
	if(posx >= dirX)
	{
		direction = 'l';
	}
	else
	{
		direction = 'r';
	}
	if(health < 1)
	{
		health = 0;
		alive = false;
	}
}