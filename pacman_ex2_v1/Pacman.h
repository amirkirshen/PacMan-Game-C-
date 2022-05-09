//ID_1: 322437815
//ID_2: 208930586
#pragma once

#include "Creature.h"

class Pacman: public Creature
{
	char arrowKeys[10] = { 's','w', 'x', 'a', 'd','S','W', 'X', 'A', 'D' };
	position original;

public:

	Pacman(const int x = 1, const int y = 1, const int _dir = 0, const char _tool = PACMAN, const int _color = WHITE);
	int getDirByKey(const char key) const;
	void reset()override;
	int move(Board &board, int& score, bool colorful = false, bool needToDraw = false);
	//position scanVerticalTunnul(Board &board, int col, int row);
	//position scanHoriontalTunnul(Board &board, int col, int row);
	//void draw(const int old_x, const int old_y, const Board& board) const;
};
