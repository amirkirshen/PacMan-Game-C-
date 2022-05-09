//ID_1: 322437815
//ID_2: 208930586
#include "Pacman.h"

Pacman::Pacman(const int x, const int y, const int _dir, const char _tool, const int _color):
	Creature(0, 0, PACMAN, x, y, _dir, YELLOW)
{
	original.setposition(x, y);
	Creature::setPos(x, y);
}

int Pacman::getDirByKey(char key) const
//get a key and return direction by format
{
	for (int i = 0; i < 10; i++)
	{
		if (key == arrowKeys[i])
			return i % 5;
	}
	return -1;
}

int Pacman::move(Board &board, int &score, bool colorful, bool needToDraw)
{
	position pos = getPos();
	int old_x = pos.getPositionX(), old_y = pos.getPositionY();
	bool flag = false;
	if (Creature::move(board, colorful) == false)
	{
		switch (getDir()) {
		case STOP:
			return true;
		case UP:
			if (getPos().getPositionY() == 0 && board.GetCoordinate(getPos().getPositionX(),board.getNumOfLines()) != BOUNDARY)
				setPos(getPos().getPositionX(), getNumOfLines() - 1);
			break;
		case DOWN:
			if (getPos().getPositionY() == board.getNumOfLines() - 1 && board.GetCoordinate(getPos().getPositionX(), 0) != BOUNDARY)
				setPos(getPos().getPositionX(), FIRST_LINE);
			break;
		case LEFT:
			if (getPos().getPositionX() == 0 && board.GetCoordinate(board.getSizeOfLine() - 2, getPos().getPositionY()) != BOUNDARY)
				setPos(getSizeOfLine() - 2, getPos().getPositionY());
			break;
		case RIGHT:
			if (getPos().getPositionX() == board.getSizeOfLine() - 2 && board.GetCoordinate(0, getPos().getPositionY()) != BOUNDARY)
				setPos(0, getPos().getPositionY());
			break;
		}
	}
	if (board.GetCoordinate(getPos().getPositionX(), getPos().getPositionY()) == FOOD)
		score++;
	if(needToDraw) Creature::draw(old_x, old_y, board, colorful);
	//if in the old position there is food - delete it and return 1 for scors
	if (board.GetCoordinate(getPos().getPositionX(),getPos().getPositionY()) == FOOD)
	{
		board.upDate(getPos().getPositionX(), getPos().getPositionY(), ' ');
		return 1;
	}
	return 0;
}

//position Pacman::scanVerticalTunnul(Board &board, int col, int row)
//{
//	int size = getNumOfLines();
//	for (int i = 0; i < size; i++)
//	{
//		if (board.GetCoordinate(col, i) == TUNNEL && i != row - 1)
//			return position(col, i);
//	}
//	cout << "oops!\nprobably the game could not scan the file successfully...\n";
//	exit(1);
//	return position(-1, -1);
//}

//position Pacman::scanHoriontalTunnul(Board &board, int col, int row)
//{
//	int size = getSizeOfLine();
//	for (int i = 0; i < size; i++)	//we might add 1 to condition
//	{
//		if (board.GetCoordinate(i, row) == TUNNEL && i != col - 1)
//			return position(i, row);
//	}
//	cout << "oops!\nprobably the game could not scan the file successfully...\n";
//	exit(1);
//	return position(-1, -1);
//}

//delete pacman and set position the the original position
void Pacman::reset()
{
	setPos(original.getPositionX(), original.getPositionY());
	setDir(0);
	gotoxy(getPos().getPositionX(), getPos().getPositionY());
	cout << ' ';
	//gotoxy(original.getPositionX(), original.getPositionY());
//	cout << PACMAN;
}