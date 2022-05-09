#pragma once
#include "Const.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <filesystem>

using std::string;
using std::vector;
enum menuChoice { BLACK_AND_WHITE = 1, COLORFUL = 2, INSTRUCTIONS = 8, EXIT = 9 };
enum methodGame { ALL_SCREEN = 1, SINGLE_SCREEN = 2 };

class  Menu
{
public:

	 void printMenu(const vector <string> &fileNames);
	 void printStructions();
	 int getUser_choice() const;
	 bool getColorful() const;
	 void setUser_choice();
	 void setColorful(int num);
	 void methodGame(const vector <string>& fileNames);
	 void setNumOfBoard(const int num);
	 void setGhostLevel(const int level);
	 int getGhostLevel() const;
	 void chooseLevel();
	 int getChoosesSingleScreen();
	 int getMethodGame() const;

private:
	int user_choice = 0;
	int method_game = 0;
	int numOfBoard = 1;
	int ghostLevel = 0;
	bool colorful = false;
};
