#pragma once

class zombie
{
public:
	zombie(void);
	~zombie(void);

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
	signed int health;
	unsigned int animateState;
	unsigned int speed;
	bool falling;
	signed int posx, posy;
	signed int minPos, maxPos;
	bool alive;
	char direction;
	GImage sprite[2][2];
	GImage dead[2];
};
