//ID_1: 322437815
//ID_2: 208930586
#pragma once
#include <iostream>
#include "Const.h"
#include <fstream>
#include <string>
#include <iomanip>
#include "Position.h"

using std::fstream;
using std::string;

class Board
{
	char gameBoard_1[ROW + 1][COL + 1];
	int wallsColor = CYAN;
	int x_ampersand_pos = 0;
	int y_ampersand_pos = 0;
	bool ampersand_appeard = false;
	int size_of_line = 0;
	int num_of_lines = 0;
	int num_of_ghost = 0;
	int num_of_pacman = 0;
	position posArr[6];
	bool boolMatrix[ROW + 1][COL + 1] = { false };
	int maxScorePerBoard = 0;

public:
	Board();
	void cleanBoard();
	void printBoard(bool colorful) const;

	//return what the matrix has in (x,y) coordinate
	char GetCoordinate(int x, int y) const;
	
	//return what the bool matrix has in (x,y) coordinate
	bool GetBoolCoordinate(int x, int y) const;

	//update in (x,y) the new char - ch
	void upDate(int x, int y, char ch);
	
	void reset(string boardName);
	void reset();
	void setColor(int color);
	int getColor() const;
	void readBoard(string boardName);
	void rebuildBoard(int& row, int& col);
	void readFirstLine(fstream& board1);
	void read19Chars(fstream& board);
	void read21Chars(fstream& board);
	void readOneChar(fstream& board, char& ch);
	int getNumOfLines();
	int getSizeOfLine();
	int getNumOfGhost();
	int getMaxScore();
	position& getCreaturePos(int i);
	position getAmpersandPos() const;
	bool isValidBoard(string boardName);
private:

	void verticalWall(int x, int y, int length);
	//build vertical wall by the programmer

	void horizontal(int x, int y, int length);
	//build horizontal wall by the programmer

};