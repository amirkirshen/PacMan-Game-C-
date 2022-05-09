#pragma once

//ID_1: 322437815
//ID_2: 208930586
#pragma once
#include "position.h"
//#include "Const.h"
//#include <iostream>
#include "Utilities.h"
#include <conio.h>
#include "Board.h"

using std::cout;
using std::cin;
enum DIR { ILLEGAl = -1, STOP, UP, DOWN, LEFT, RIGHT };

class Creature
{
	position pos;
	char tool;
	int dir = 0;	// 0-stop, 1-up, 2 - down, 3 -left , 4 - right
	int color = WHITE;
	int size_of_line = 0;
	int num_of_lines = 0;

public:

	Creature(int numOfLines, int sizeOfLine, const char _tool, const int x = 1, const int y = 1, const int _dir = 0, const int _color = WHITE);
	Creature();
	//position& getPos();
	position getPos() const;
	int getDir() const;
	void setDir(int newDir);
	void setTool(const int newTool);
	char getTool() const;
	void setColor(int Color);
	void setPos(const int x, const int y);
	int getColor() const;
	virtual bool move(Board board, bool colorful = false, bool needToDraw = false);
	void draw(const int old_x, const int old_y, const Board& board, bool colorful) const;
	virtual void reset() = 0;
	void setNumOfLines(const int num);
	void setSizeOfLine(const int num);
	int getNumOfLines();
	int getSizeOfLine();
};