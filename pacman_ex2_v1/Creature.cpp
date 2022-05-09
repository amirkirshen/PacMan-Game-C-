//ID_1: 322437815
//ID_2: 208930586
#include "Creature.h"

Creature::Creature(int numOfLines, int sizeOfLine, const char _tool, const int x, const int y, const int _dir, const int _color)
{
	pos.setposition(x, y);
	dir = _dir;
	tool = _tool;
	color = _color;
	num_of_lines = numOfLines;
	size_of_line = sizeOfLine;
};

Creature::Creature()
{
	pos = position(1, 1);
	dir = STOP;
	tool = PACMAN;
	color = WHITE;
}

void Creature::setPos(const int x, const int y)
{
	pos.setposition(x, y);
}

int Creature::getDir() const
{
	return dir;
}

void Creature::setDir(int newDir)
{
	dir = newDir;
}

void Creature::setTool(int newTool)
//set the character that represents the creature
{
	tool = newTool;
}

char Creature::getTool() const
//return the character that represents the creature
{
	return tool;
}

position Creature::getPos() const
//set the creature position
{
	return this->pos;
}

void Creature::setColor(int _color)
//set the creature color
{
	color = _color;
}

int Creature::getColor() const
{
	return color;
}

bool Creature::move(Board board, bool colorful, bool needToDraw)
//public - make the object move in the selected direction
{
	int old_x = pos.getPositionX(), old_y = pos.getPositionY();
	bool flag = false;
	switch (dir) {
	case STOP:
		flag = true;
		break;
	case UP:
		if (board.GetCoordinate(pos.getPositionX(),pos.getPositionY() - 1) != BOUNDARY && pos.getPositionY() > 0)
		{
			pos.setposition(pos.getPositionX(), pos.getPositionY() - 1);
			flag = true;
		}
		else return false;
		break;
	case DOWN:
		if (board.GetCoordinate(pos.getPositionX(),pos.getPositionY() + 1) != BOUNDARY && pos.getPositionY() < num_of_lines - 1)
		{
			pos.setposition(pos.getPositionX(), pos.getPositionY() + 1);
			flag = true;
		}
		else return false;
		break;
	case LEFT:
		if (board.GetCoordinate(pos.getPositionX() - 1,pos.getPositionY()) != BOUNDARY && pos.getPositionX() > 0)
		{
			pos.setposition(pos.getPositionX() - 1, pos.getPositionY());
			flag = true;
		}
		else return false;
		break;
	case RIGHT:
		if (board.GetCoordinate(pos.getPositionX() + 1,pos.getPositionY()) != BOUNDARY && pos.getPositionX() < size_of_line - 2)
		{
			pos.setposition(pos.getPositionX() + 1, pos.getPositionY());
			flag = true;
		}
		else return false;
		break;
	}
	if ((flag == true || tool == PACMAN) && needToDraw)
	{
		draw(old_x, old_y, board, colorful);
	}
	return flag;
}

//draw the creature moovment - draw the next pos and delete the old one
void Creature::draw(const int old_x, const int old_y, const Board &board, bool colorful) const
{
	gotoxy(old_x, old_y);
	cout << board.GetCoordinate(old_x, old_y);
	gotoxy(pos.getPositionX(), pos.getPositionY());
	if (colorful)setTextColor(color);
	cout << tool;
	if (colorful)setTextColor(WHITE);
}

void Creature::setNumOfLines(const int num)
{
	num_of_lines = num;
}

void Creature::setSizeOfLine(const int num)
{
	size_of_line = num;
}

int Creature::getNumOfLines()
{
	return num_of_lines;
}

int Creature::getSizeOfLine()
{
	return size_of_line;
}