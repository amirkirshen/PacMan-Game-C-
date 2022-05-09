//ID_1: 322437815
//ID_2: 208930586
#pragma once
#include <iostream>
#include <Windows.h>
#include "Const.h"
#include <time.h>

using std::cout;
using std::cin;



class position
{
	int x = 5, y = 5;


public:
	position(int x = 0, int y = 0);
	void setposition(const int _x, const int _y);
	void setposition(position newPos, const int delta_x, const int delta_y);
	int getPositionX() const;
	int getPositionY() const;

	bool operator==(const position& pos2) const
	{
		return ((this->x == pos2.x) && (this->y == pos2.y));
	};
};
