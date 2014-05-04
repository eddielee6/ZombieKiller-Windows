#pragma once

class hitler
{
public:
	hitler(void);
	~hitler(void);

	void draw(GWindow* Gwin);
	void animate();
	signed int getX();
	signed int getY();
	signed int getHealth();
	void setup(int x, int y, char dir, int minX, int maxX, int newHealth, bool spawn);
	void fall();
	void setFalling(bool fall);
	void attacked(int damage, signed int dirX, bool melee);
	bool isAlive();

private:
	GImage sprite[14];
	signed int health;
	bool nextFrame;
	unsigned int animateState;
	unsigned int speed;
	bool falling;
	signed int posx, posy;
	signed int minPos, maxPos;
	bool alive;
	char direction;
};
