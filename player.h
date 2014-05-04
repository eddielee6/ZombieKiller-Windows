#pragma once

class player
{
public:
	player(void);
	~player(void);

	//Do
	void drawPlayer(GWindow* Gwin);
	void faceRight(bool state);
	void endJump();
	void moveY(char type);
	void moveX(char type);
	void freeFall();
	void down(bool state);
	void moving(char direction);
	void stopWalking();
	void gainedHealth();
	void lostMana(int amount);
	void gainedMana(int amount);
	void gravity(backgroundManager* bkground);
	void isAttacked();
	bool isAlive();
	void respawn();
	void resetHealth();


	bool getJumpStatus();
	bool jump();
	bool checkDown();

	//Get
	signed int getHealth();
	signed int getMana();
	signed int getX();
	signed int getY();
	char getDir();

private:

	//Used in game
	signed int health;
	signed int mana;
	signed int X, Y;
	unsigned int speed;
	unsigned int attackLoop;

	//Used in class
	unsigned int spriteState, walkState;
	unsigned int jumpHeight;
	bool isRight;
	bool isDown;
	bool jumping;
	bool walking;
	bool inAir;
	bool attacked;
	
	//Player Image States
	GImage spriteL[3];
	GImage spriteR[3];
	GImage spriteWalkL[8];
	GImage spriteWalkR[8];
	GImage spriteJump[2];
	GImage spriteDown[2];
	GImage dead[2];
};
