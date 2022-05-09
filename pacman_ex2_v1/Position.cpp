//ID_1: 322437815
//ID_2: 208930586

#include "Position.h"
#include <iostream>
//#include "Utilities.h"	// might be remove

using std::cout;
using std::cin;
using std::endl;

position::position(int _x, int _y)
{
	x = _x;
	y = _y;
}

void position::setposition(int _x, int _y)
//public - Allows you to update position
{
	x = _x;
	y = _y;
}

void position::setposition(position newPos, int delta_x = 0, int delta_y = 0)
//public - Allows you to update position
//delta x/y in case we want to  change position by deltas and not by another position
{
	x = newPos.x + delta_x;
	y = newPos.y + delta_y;
}

int position::getPositionX() const
{
	return x;
}

int position::getPositionY() const
{
	return y;
}