#pragma once

#include "GameManager.h"

class SimpleMode : virtual public GameManager
{
public:
	//SimpleMode();
	void resetGame();
	virtual void run() override;
	void playSingleScreen();
	void GhostsetLevel();
	void playAllScreen();
	void looseMessage();
	void winMessage();
	void printlegend();
	void printScoreBoard();
	void printScore();
	void printLife();
	virtual bool startGame();
	void setCreatureDir();
	void chooseDirForFruit(position pos);
	bool isValidStep(int row, int col);
	void moveAllCreaturs(bool draw, bool colorful);
	Creature** getCreatureArrFromGameManager();
	int getGameCounter();
	int getGameNumOfGhosts();
	int getCurrBoard();
	void setCurrBoard(int screen);
	int getScore();
	int getLife();
	int getGhostLevel();

protected:
	bool colorful = false;
	int numOfScreen = 0;
	Menu menu;
private:
	
};
