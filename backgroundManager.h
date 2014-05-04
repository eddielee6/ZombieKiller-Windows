#pragma once

class backgroundManager
{
public:
	backgroundManager(void);
	~backgroundManager(void);

	void draw(GWindow* Gwin);
	void nextLevel();
	void changeMenu(std::string direction);
	void pauseGame();
	void mapSetup();
	void pauseMenu(GWindow* Gwin);
	void drawDeadScreen(GWindow* Gwin);
	void storyMenu(GWindow* Gwin, gameTime* gameTimer);
	bool isComplete();
	bool isStory();
	void resetMenuToggle(char type);
	void menuClick();
	void deadGuy();
	void setStoryMenu();
	void levelAdvance();
	bool isPlaying();
	unsigned int getPlatformQuant();
	int getGroundLevel();
	int	platformY(unsigned int num);
	int	platformX(unsigned int num);
	int	platformHeight(unsigned int num);
	int	platformWidth(unsigned int num);
	int getLeftBound();
	int getRightBound();
	int currentLevel();
	void startScreen(GWindow* Gwin);
	bool isInGame();
	bool resetMap();
	void hasReset();
	void removeClickLock();
	std::string menuType();

private:
	bool clickLock;
	GImage bkImage;
	GImage menuImages[3][2];
	std::string activeMenu;
	GImage menuBk;
	GImage startScreenBk;
	GImage deadScreenBk;
	GImage storyScreenBk[4];
	GRect screen;
	platforms gamePlatforms[5];
	unsigned int platX[5], platY[5];
	unsigned int leftBound;
	unsigned int rightBound;
	unsigned int groundLevel;
	unsigned int level;
	unsigned int deadScreenScrollH;
	unsigned int deadScreenScrollY;
	bool setMenuItem;
	bool inGame;
	bool storyLine;
	bool complete;
	bool reset;
	char optionChangeToggle;
	bool playing;
	bool deadMenu;
	signed int menuItem;
};
