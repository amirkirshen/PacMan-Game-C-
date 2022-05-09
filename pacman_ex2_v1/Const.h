//ID_1: 322437815
//ID_2: 208930586
#pragma once
#include <iostream>
enum gameLevel { NOVICE = 1, GOOD, BEST };

const char FOOD = '\'';
const char PACMAN = 'c';
const char GHOST = '$';
const char TUNNEL = '@';
const char ESC = 27;	
const char BOUNDARY = char(219);
const int ROW = 25;
const int COL = 80;
const int FLOOR = 23;
const int WALL_R = 80;
const int WALL_L = 0;
const int CEIL = 0;
const int DELTA = 10;
const int MAX_SCORS = ((78 * 21) - 204);
const int FIRST_LINE = 0;
const int X_LIFE_STATUS = 3;
const int Y_LIFE_STATUS = 20;
const int SCREEN_CENTER_X = 40;
const int SCREEN_CENTER_Y = 10;

enum Colors
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};
