#include "StdAfx.h"
#include "gameTime.h"
#include <sstream>
#include <string>

gameTime::gameTime(void)
{
	min = 0;
	sec = 0;
	time = 0;
}

gameTime::~gameTime(void)
{
}

void gameTime::increaseTime()
{
	++sec;
	++time;
	if(sec >= 60)
	{
		min++;
		sec = 0;
	}
}

std::string gameTime::convertInt(int number)
{
	std::stringstream strStream;
	std::string myString; //Target string variable
	int myInt = number; //Number to convert

	strStream << myInt;
	myString = strStream.str(); //myString should now be "5"

	return myString;
}

unsigned int gameTime::getElapsedTime()
{
	return time;
}

std::string gameTime::getGameTime()
{
	//Calculate If Leading Zero Is Needed
	bool addMinZero = false;
	bool addSecZero = false;
	if(min < 10)
	{
		addMinZero = true;
	}
	if(sec < 10)
	{
		addSecZero = true;
	}
	
	std::string gameTime;
	std::string minTime = convertInt(min);
	std::string secTime = convertInt(sec);
	std::string zero = "0";
	std::string colon = ":";

	if(addMinZero)
	{
		gameTime += zero;
	}
	gameTime += minTime;
	gameTime += colon;
	if(addSecZero)
	{
		gameTime += zero;
	}
	gameTime += secTime;

	return gameTime;
}