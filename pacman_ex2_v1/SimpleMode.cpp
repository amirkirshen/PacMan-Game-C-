#include "SimpleMode.h"

enum creatureType { PACMAN_TYPE, FRUIT_TYPE, GHOST_TYPE };

//enum userChoice { ALL_SCREEN = 1, SINGLE_SCREEN = 2, EXIT = 9 };
using std::endl;
using std::vector;
const int numOfCreature = 6;

//SimpleMode::SimpleMode()
//	: GameManager()
//{
//
//}

//runs and manages the all game
void SimpleMode::run()
{
	static bool allReadyLoad = false;
	//prevents reloading
	if (!allReadyLoad)
	{
		allReadyLoad = true;
		getFilesNames();
	}

	//switch case by user choice
	do
	{
		//print menu and updates board's names in 'filenames' vector
		menu.printMenu(GameManager::getStringFiles());
		//end the game if user choose exit
		if (menu.getUser_choice() == EXIT) break;
		switch (menu.getMethodGame())
		{
		case ALL_SCREEN:
			playAllScreen();
			break;
		case SINGLE_SCREEN:
			playSingleScreen();
			break;
		default:
			system("CLS");
			cout << "game failur";
			break;
		}
		resetGame();
	} while (menu.getUser_choice() != EXIT);
	system("CLS");
	cout << "good bye" << endl << endl;
}

//resets the game to pre-run status
void SimpleMode::resetGame()
{
	system("CLS");
	setScore(0);
	setNumOfLife(3);
	numOfPacmanSteps = 0;
	getBoard().reset();
	menu.setColorful(false);
	//Board1.reset();
}

//runs single game
bool SimpleMode::startGame()
{
	bool haveMoreLife = true;
	char key = 0;
	system("CLS");
	setCreature();
	GhostsetLevel();
	getBoard().printBoard(menu.getColorful());
	printlegend();
	do
	{
		if (_kbhit())
		{
			key = _getch();
			setPacmanDir(key);
		}

		movePacman(true, colorful);
		eat();
		printScore();
		if (getNumOfLife() <= 0) break;
		if (pacmanMoove == true)
		{
			moveAllCreaturs(true, colorful);
			printLife();
			if (menu.getGhostLevel() == 2 && getNumOfGhost() <= 2) Sleep(100);
			if (menu.getGhostLevel() < 2) Sleep(170);
			Sleep(60 / menu.getGhostLevel());
			eat();
			if (getNumOfLife() <= 0) break;
			pacmanMoove = false;
		}
		else
		{
			Sleep(15 * (getNumOfGhost() + (3 * menu.getGhostLevel())));
			pacmanMoove = true;
		}
		if (key == ESC)
			//in case the user clicks 'esc' - the game is stop
			//another 'esc' to continue
		{
			do
			{
				key = _getch();
			} while (key != ESC);
			key = '0' + 1;
		}
		if (getScore() == getMaxScore())
		{
			break;
		}
	} while (key != -1);
	return (getNumOfLife() > 0);
}

//inserts each creature dir to arrDir
void SimpleMode::setCreatureDir()
{
	Fruit* fruit = dynamic_cast <Fruit*> (getcreatureArr()[1]);
	Ghost* ghost = nullptr;

	chooseDirForFruit(fruit->getPos());
	for (int i = 2; i < 2 + getNumOfGhost(); i++)
	{
		ghost = dynamic_cast <Ghost*> (getcreatureArr()[i]);
		if(ghost) ghost->chooseDir(getBoard(), getcreatureArr()[0]->getPos(), ghost->getIsSmart());
		getMoveArr()[i] = ghost->getDir();
	}
}

Creature** SimpleMode::getCreatureArrFromGameManager()
{
	return (getcreatureArr());
}

int SimpleMode::getGameCounter()
{
	return getCounter();
}

int SimpleMode::getGameNumOfGhosts()
{
	return getNumOfGhost();
}

int SimpleMode::getCurrBoard()
{
	return getCurrBoardNum();
}

void SimpleMode::setCurrBoard(int screen)
{
	menu.setNumOfBoard(screen);
}

int SimpleMode::getScore()
{
	return GameManager::getScore();
}

int SimpleMode::getLife()
{
	return getNumOfLife();
}

int SimpleMode::getGhostLevel()
{
	return menu.getGhostLevel();
}

//sets level for each ghost according to user choice
void SimpleMode::GhostsetLevel()
{
	Ghost* ghost = NULL;
	int level = menu.getGhostLevel();
	int numOfGhost = getNumOfGhost();
	for (int i = 2; i < 2 + numOfGhost; i++)
	{
		ghost = dynamic_cast<Ghost*>(getcreatureArr()[i]);
		if (ghost)
			ghost->setLevel(level);
	}
}

//chooses random direction to fruit
void SimpleMode::chooseDirForFruit(position pos)
{
	int dRow[] = { -1, 0, 1, 0 };
	int dCol[] = { 0, 1, 0, -1 };
	int y = pos.getPositionY();
	int x = pos.getPositionX();
	for (int i = 0; i < 4; i++)
	{
		int adjy = y + dRow[i];
		int adjx = x + dCol[i];
		if (isValidStep(adjy, adjx))
			getcreatureArr()[2]->setDir(i + 1);
	}
}

//runs a game for a single screen mode
void SimpleMode::playSingleScreen()
{
	bool isWin = false;
	setCurrBoardNum(menu.getChoosesSingleScreen());
	//reads the board that user choose
	getBoard().readBoard(getStringFiles()[menu.getChoosesSingleScreen() - 1]);
	setMaxScore(getBoard().getMaxScore());
	isWin = startGame();
	if (!isWin) looseMessage();
	else winMessage();
	resetGame();
}

//runs the all screens in a row
void SimpleMode::playAllScreen()
{
	bool isWin = false;
	for (const auto& p : getStringFiles())
	{
		getCurrBoardNum()++;
		getBoard().readBoard(p);
		setMaxScore(getMaxScore() + getBoard().getMaxScore());
		isWin = startGame();
		if (!isWin)
		{
			looseMessage();
			break;
		}
		else if ((unsigned)getCurrBoardNum() < getStringFiles().size())
		{
			char ch;
			system("CLS");
			gotoxy(SCREEN_CENTER_X, SCREEN_CENTER_Y);
			cout << "you win screen number: " << getCurrBoardNum() << "  score: " << getScore();
			gotoxy(SCREEN_CENTER_X, SCREEN_CENTER_Y + 1);
			cout << "press any key to continue to the next screen" << endl << endl;
			ch = _getch();
			system("CLS");
		}
		getBoard().cleanBoard();
		numOfPacmanSteps = 0;
	}
	if (isWin)
		winMessage();
}

void SimpleMode::looseMessage()
{
	char ch;
	system("CLS");
	gotoxy(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	cout << "you lose... maybe next time";
	gotoxy(SCREEN_CENTER_X, SCREEN_CENTER_Y + 1);
	cout << "press any key to continue" << endl << endl;
	ch = _getch();
	system("CLS");
}

void SimpleMode::winMessage()
{
	char ch;
	system("CLS");
	gotoxy(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	cout << "you win!   score: " << getScore();
	gotoxy(SCREEN_CENTER_X, SCREEN_CENTER_Y + 1);
	cout << "press any key to continue" << endl << endl;
	ch = _getch();
	system("CLS");
}

void SimpleMode::printScoreBoard()
{
	printScore();
	printLife();
}

void SimpleMode::printlegend()
{
	position AmpersandPos = getBoard().getAmpersandPos();
	gotoxy(AmpersandPos.getPositionX(), AmpersandPos.getPositionY());
	cout << "scores: " << getScore();
	switch (getNumOfLife())
	{
	case 3:
		gotoxy(AmpersandPos.getPositionX(), AmpersandPos.getPositionY() + 1);
		cout << "life: ";
		if (menu.getColorful())setTextColor(RED);
		cout << "<3 <3 <3";
		if (menu.getColorful())setTextColor(WHITE);
		break;
	case 2:
		gotoxy(AmpersandPos.getPositionX(), AmpersandPos.getPositionY() + 1);
		cout << "life: ";
		if (menu.getColorful())setTextColor(RED);
		cout << "<3 <3";
		if (menu.getColorful())setTextColor(WHITE);
		break;
	case 1:
		gotoxy(AmpersandPos.getPositionX(), AmpersandPos.getPositionY() + 1);
		cout << "life: ";
		if (menu.getColorful())setTextColor(RED);
		cout << "<3";
		if (menu.getColorful())setTextColor(WHITE);
	}
	gotoxy(AmpersandPos.getPositionX(), AmpersandPos.getPositionY() + 2);
	cout << "board: " << getCurrBoardNum();
}

void SimpleMode::printScore()
{
	position AmpersandPos = getBoard().getAmpersandPos();
	gotoxy(AmpersandPos.getPositionX() + 8, AmpersandPos.getPositionY());
	if (menu.getColorful())setTextColor(LIGHTMAGENTA);
	cout << getScore();
	if (menu.getColorful())setTextColor(WHITE);
}

void SimpleMode::printLife()
{
	position AmpersandPos = getBoard().getAmpersandPos();
	
	switch (getLife())
	{
	case 2:
		gotoxy(AmpersandPos.getPositionX() + 12, AmpersandPos.getPositionY() + 1);
		break;
	case 1:
		gotoxy(AmpersandPos.getPositionX() + 9, AmpersandPos.getPositionY() + 1);
		break;
	default:
		return;
		break;
	}
	cout << "  ";
}


bool SimpleMode::isValidStep(int row, int col)
{
	// If cell is bounds
	if (row >= getBoard().getNumOfLines() || col >= getBoard().getSizeOfLine())
		return false;

	// If cell is bounds
	if (getBoard().GetCoordinate(col, row) == BOUNDARY || getBoard().GetCoordinate(col, row) == TUNNEL)
		return false;

	// Otherwise
	return true;
}


//call move for each creature except pacman move
//need dynamic cast
void SimpleMode::moveAllCreaturs(bool draw, bool colorful)
{
	Ghost* ghost = NULL;
	Fruit* fruit = NULL;
	static bool j;
	int numOfGhost = getNumOfGhost();
	makeFruit();
	fruit = dynamic_cast<Fruit*>(getcreatureArr()[1]);
	if (fruit)
	{
		fruit->moveAndDraw(getBoard(), ILLEGAl, colorful);
	}
	for (int i = 2; i < 2 + numOfGhost; i++)
	{
		ghost = dynamic_cast<Ghost*>(getcreatureArr()[i]);
		if (ghost)
		{
			ghost->moveAndDraw(getBoard(), ILLEGAl, getcreatureArr()[PACMAN_TYPE]->getPos(), colorful, j);
		}

		if (j == true)
			j = false;
		else
			j = true;
		if (numOfPacmanSteps % (numOfCreature - 1) == 0) j = true;
	}
	//allways calculte to other ghost: 1->3->2->4->1->3...
	if (numOfGhost % 2 == 0)
		switch (j)
		{
		case true:
			j = false;
			break;
		case false:
			j = true;
			break;
		}
}