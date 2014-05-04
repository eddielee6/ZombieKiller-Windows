#pragma once

class gameTime
{
public:
	gameTime(void);
	~gameTime(void);

	std::string getGameTime();
	unsigned int getElapsedTime();
	void increaseTime();

private:
	std::string convertInt(int number);
	int min;
	int sec;
	int time;
};
