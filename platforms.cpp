#include "StdAfx.h"
#include "platforms.h"

platforms::platforms()
{
	platformImage.loadImage("Sprites/Platform.png");
	
	width = platformImage.getWidth();
	height = platformImage.getHeight();
}

platforms::~platforms(void)
{
}

void platforms::drawPlatform(unsigned int newX, unsigned int newY, GWindow* Gwin)
{
	X = newX;
	Y = newY;
	Gwin->drawImage(X,Y,&platformImage);
}
int platforms::getX()
{
	return X;
}
int platforms::getY()
{
	return Y;
}
int platforms::getWidth()
{
	return width;
}
int platforms::getHeight()
{
	return height;
}