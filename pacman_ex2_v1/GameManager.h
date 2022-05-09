#pragma once

//#include <iostream>
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Menu.h"
#include "Const.h"
#include <filesystem>

using std::vector;

class GameManager
{
public:
	GameManager();
	GameManager(const GameManager& copy);
	~GameManager();
	virtual void run() = 0;
	GameManager& operator=(const GameManager& other);
	bool eat();
	void creatureReset();
	void setPacmanDir(int key);
	void moveAllCreaturs(bool draw = false, bool colorful = false);		//neet to rebuild = 0;
	void movePacman(bool draw, bool colorful);
	void makeFruit();			//need to rebuild = 0;
	void getFilesNames();
	int &getCurrBoardNum();
	void setCurrBoardNum(int screen);
	Creature** getcreatureArr();
	int getCounter();
	void raiseCounter();
	int getNumOfGhost();
	int getNumOfLife();
	void setNumOfLife(int life);
	int getScore();
	void setScore(int score);
	int &getScoreByRef();
	int getMaxScore();
	void setMaxScore(int score);
	const vector<string> &getStringFiles();
	void setCreature();
	Board& getBoard();
	int* getMoveArr();
	int getGhostLevel();
	void updateLife();

protected:
	int numOfStepsToFruit = 0;
	int numOfPacmanSteps = 0;
	bool pacmanMoove = false;	//faster pacman - ghost moove only when true


private:
	vector <string> filenames;
	Board Board1;
	unsigned long int counter = 0;
	Creature* arrCreature[6];
	int life = 3;
	int numOfGhost = 1;
	int moveArr[6] = {0};
	int currScreen = 0;
	int ghostLevel = 0;
	int score = 0;
	int maxScore = 0;
};