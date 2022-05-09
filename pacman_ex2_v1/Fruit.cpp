//ID_1: 322437815
//ID_2: 208930586

#include "Utilities.h"
#include "Fruit.h"

using std::cout;
using std::cin;
using std::endl;

Fruit::Fruit(const int _x, const int _y, const int _dir, Board &board, const int _color, int value) :
	Creature(_x, _y, _dir, value + '0', LIGHTRED)
{
	isExist = false;
	randomFruit();
	randomPos(board);
}

Fruit::Fruit(): Creature(26, 26, UP, '5', WHITE)
{
	isExist = false;
}

void Fruit::reset()
{
	SetisExist(false);
}

void Fruit::SetisExist(bool exp)
{
	isExist = exp;
	if (exp)
		setTool(value + '0');
}
bool Fruit::GetisExist() const
{
	return isExist;
}

int Fruit::getValue() const
{
	return value;
}

int Fruit::getTimeOfLife() const
{
	return time_of_life;
}

void Fruit::setValue(const int newVal)
{
	value = newVal;
}

//make a random fruit (random life and random value)
void Fruit::randomFruit()
{
	value = (rand() % 5 + 3);
	time_of_life = (rand() % 40) + (80 - value);
	setTool(char(value + int('0')));
}

//find random position to start
void Fruit::randomPos(Board &board)
{
	int x, y;
	do
	{
		x = rand() % getSizeOfLine();
		y = rand() % getNumOfLines();

	} while (board.GetBoolCoordinate(x, y) == false);
	setPos(x, y);
}

//just move
void Fruit::move(Board& board, int dir, bool colorful)
{
	position tempPos = this->getPos();
	if (isExist)
	{
		while ((!Creature::move(board, colorful)) && dir == -1)
			setDir(rand() % 4 + 1);

	}
	//gotoxy(tempPos.getPositionX(), tempPos.getPositionY());
	//cout << board.GetCoordinate(tempPos.getPositionX(), tempPos.getPositionY());
}

//move and draw
void Fruit::moveAndDraw(Board& board, int dir, bool colorful)
{
	int old_x = getPos().getPositionX(), old_y = getPos().getPositionY();
	if (isExist)
	{
		move(board, dir, colorful);
		draw(old_x, old_y, board, colorful);
	}
}

void Fruit::draw(int old_x, int old_y, Board &board, bool colorful) const
{
	if (isExist)
		Creature::draw(old_x, old_y, board, colorful);
}

//restart the fruit if it is not exist
void Fruit::relife(Board& board)
{
	if (isExist)
	{
		gotoxy(getPos().getPositionX(), getPos().getPositionY());
		cout << board.GetCoordinate(getPos().getPositionX(), getPos().getPositionY());
	}
	isExist = true;
	randomFruit();
	randomPos(board);
	setDir(rand() % 4 + 1);
}
