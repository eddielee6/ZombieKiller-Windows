#pragma once

class platforms
{
public:
	platforms();
	~platforms(void);

	void drawPlatform(unsigned int newX, unsigned int newY, GWindow* Gwin);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

private:
	GImage platformImage;
	unsigned int X,Y;
	unsigned int width,height;
};
