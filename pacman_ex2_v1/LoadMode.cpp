#include "LoadMode.h"

using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;


//start a single game
bool LoadMode::startGame(string stepsScreen, string resScreen)
{
	ifstream stepFile, resFile;
	Creature* cretPtr = nullptr;
	system("CLS");
	getBoard().printBoard(false);
	SimpleMode::printlegend();
	stepFile.open(stepsScreen);
	resFile.open(resScreen);
	int dir, creature, numOfGhost = getNumOfGhost();
	bool isSucceed = true;
	while (!stepFile.eof() && getNumOfLife() > 0 && getScore() < getMaxScore())
	{
		SimpleMode::printScoreBoard();
		readOneWordFromFile(creature, dir, stepFile);
		cretPtr = getcreatureArr()[creature];
		cretPtr->setDir(dir);
		Pacman* pacPtr = dynamic_cast<Pacman*>(cretPtr);
		Fruit* fruitPtr = dynamic_cast<Fruit*>(cretPtr);
		if (pacPtr)
			pacPtr->move(getBoard(), getScoreByRef(), false, true);
		else if (fruitPtr)
			moveOrCleanFruit(fruitPtr);
		else
			cretPtr->move(getBoard(), false, true);
		Sleep(5 / numOfGhost);
		if (eat())
		{
			if (!checkIfGotEatenOnTime(resFile))
			{
				isSucceed = false;
				break;
			}
		}
	}
	isSucceed = isSucceed && checkIfResIsMatching(resFile, "screen life's", getNumOfLife());
	if (getNumOfLife() != 0)isSucceed = isSucceed && checkIfResIsMatching(resFile, "screen finish at", getCounter());
	return isSucceed;
}

void LoadMode::run()
{
	SilentMode::run();
}

void LoadMode::moveOrCleanFruit(Fruit* fruitPtr)
{
	int x = fruitPtr->getPos().getPositionX(), y = fruitPtr->getPos().getPositionY();
	if (fruitPtr->GetisExist())fruitPtr->moveAndDraw(getBoard(), fruitPtr->getDir(), false);
	else
	{
		gotoxy(x, y);
		cout << getBoard().GetCoordinate(x, y);
	}
}
