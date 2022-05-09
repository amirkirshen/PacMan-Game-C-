#include "GameManager.h"

enum creatureType { PACMAN_TYPE , FRUIT_TYPE, GHOST_TYPE};
//enum userChoice { ALL_SCREEN = 1, SINGLE_SCREEN = 2, EXIT = 9 };
using std::endl;
class SimpleMode;

GameManager::GameManager()
{
	bool flag = true;
	srand(unsigned int(time(NULL)));
	numOfGhost = Board1.getNumOfGhost();
	for (int i = 0; i < 2 + numOfGhost; i++)
	{
		switch (i)
		{
		case PACMAN_TYPE:
			arrCreature[i] = new Pacman(Board1.getCreaturePos(i).getPositionY(), Board1.getCreaturePos(i).getPositionX());
			break;
		case FRUIT_TYPE:
			arrCreature[i] = new Fruit();
			break;
			
		default:
			if (i % 2 == 0) flag = false;
			arrCreature[i] = new Ghost(Board1.getCreaturePos(i).getPositionY(), Board1.getCreaturePos(i).getPositionX());
			break;
		}
	}
}

//copy ctor does not copy the 'arrCreature'
GameManager::GameManager(const GameManager& copy)
{
	Board1 = copy.Board1;
	numOfGhost = copy.numOfGhost;
	numOfStepsToFruit = copy.numOfStepsToFruit;
	numOfPacmanSteps = copy.numOfPacmanSteps;

	int score = copy.score;
	int life = copy.life;
	bool pacmanMoove = copy.pacmanMoove;
	for (int i = 0; i < 6; i++)
	{
		arrCreature[i] = nullptr;
	}
}

GameManager::~GameManager()
{
	for (int i = 0; i < 2 + numOfGhost; i++)
	{
		delete (arrCreature[i]);
	}
}

Board& GameManager::getBoard()
{
	return Board1;
}

//jest copy other.filenames
GameManager& GameManager::operator=(const GameManager& other)
{
	this->counter = 0;
	this->filenames = other.filenames;
	for (int i = 0; i < 6; i++)
	{
		this->arrCreature[i] = nullptr;
	}
	return *this;
}

void GameManager::run()
{
	static bool allReadyLoad = false;
	//prevents reloading
	if (!allReadyLoad)
	{
		allReadyLoad = true;
		getFilesNames();
	}

	
}

int GameManager::getCounter()
{
	return counter;
}

void GameManager::raiseCounter()
{
	counter++;
}

int GameManager::getNumOfGhost()
{
	return numOfGhost;
}


//check if one of the ghosts eats pacman
//return true if yes or false for no
bool GameManager::eat()
{
	bool flag = false;
	position ghostPos = arrCreature[2][0].getPos();
	position pacmanPos = arrCreature[0][0].getPos();
	Fruit *fruit = NULL;
	fruit = dynamic_cast<Fruit*>(arrCreature[1]);
	
	//check if pacman eat fruit
	//need a dynamic cast for useing GetisExist()
	if (fruit)
	{
		if (fruit->getPos() == arrCreature[0][0].getPos() && fruit->GetisExist())
		{
			//delete the creature and print the char that in the same pos
			//reset fruit and update score
			gotoxy(fruit->getPos().getPositionX(), fruit->getPos().getPositionY());
			cout << Board1.GetCoordinate(fruit->getPos().getPositionX(), fruit->getPos().getPositionY());
			fruit->reset();
			fruit->SetisExist(false);
			score += fruit->getValue();
			maxScore += fruit->getValue();
			//flag = true;
		}
	}

	//check if ghost eat pacman
	for (int i = 2; i < 2 + numOfGhost; i++)
	{
		if (arrCreature[i][0].getPos() == arrCreature[0][0].getPos())
		{
			creatureReset();
			life--;

			flag = true;
		}
	}
	//if (life == 0)
	return flag;
}


int GameManager::getNumOfLife()
{
	return life;
}

void GameManager::setNumOfLife(int life)
{
	this->life = life;
}

void GameManager::updateLife()
{
	life--;
}

int &GameManager::getCurrBoardNum()
{
	return currScreen;
}

void GameManager::setCurrBoardNum(int screen)
{
	currScreen = screen;
}

int GameManager::getScore()
{
	return score;
}

void GameManager::setScore(int score)
{
	this->score = score;
}

int& GameManager::getScoreByRef()
{
	return score;
}

int GameManager::getMaxScore()
{
	return maxScore;
}

void GameManager::setMaxScore(int score)
{
	maxScore = score;
}

const vector<string> &GameManager::getStringFiles()
{
	return filenames;
}

//resets all the creatures
void GameManager::creatureReset()
{
	for (int i = 0; i < numOfGhost + 2; i++)
	{
		//delete creatures from board
		gotoxy(arrCreature[i][0].getPos().getPositionX(), arrCreature[i][0].getPos().getPositionY());
		if (i != 1) cout << Board1.GetCoordinate(arrCreature[i][0].getPos().getPositionX(), arrCreature[i][0].getPos().getPositionY());

		//reset all creatures
		if (i != 1) arrCreature[i][0].reset();
	}
}

//update pac dir by calling getDirKey
//need dynamic cast for this
void GameManager::setPacmanDir(int key)
{
	Pacman* pac = NULL;
	pac = dynamic_cast<Pacman*>(arrCreature[PACMAN_TYPE]);
	if (pac && key != ILLEGAl && pac->getDirByKey(key) != ILLEGAl)
		pac->setDir(pac->getDirByKey(key));
}

//call pacman move
//need dynamic cast
//the function called more frequently, therefore separately from the other move funcs
void GameManager::movePacman(bool draw, bool colorful)
{
	Pacman* pac = NULL;
	pac = dynamic_cast<Pacman*>(arrCreature[PACMAN_TYPE]);
	if (pac)
	{
		pac->move(Board1, score, colorful, draw);
		numOfPacmanSteps++;
	}
	counter++;
}


//call move for each creature except pacman move
//need dynamic cast
void GameManager::moveAllCreaturs(bool draw , bool colorful)
{
	Ghost* ghost = NULL;
	Fruit* fruit = NULL;
	static bool j = true;
	makeFruit();
	fruit = dynamic_cast<Fruit*>(arrCreature[1]);
	if (fruit)
	{
		fruit->move(Board1, moveArr[1], colorful);
	}
	for (int i = 2; i < 2 + numOfGhost; i++)
	{
		ghost = dynamic_cast<Ghost*>(arrCreature[i]);
		if (ghost)
			ghost->move(Board1, moveArr[i], arrCreature[PACMAN_TYPE]->getPos(), j);
		if (j == true)
			j = false;
		else
			j = true;
		if (numOfPacmanSteps % 5 == 0) j = true;
	}
	if(numOfGhost%2 == 0)
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

int* GameManager::getMoveArr()
{
	return moveArr;
}

int GameManager::getGhostLevel()
{
	return ghostLevel;
}

//make a new fruit in random time and space
void GameManager::makeFruit()
{
	Fruit* fruit = NULL;
	fruit = dynamic_cast<Fruit*>(arrCreature[1]);
	if (fruit)
	{
		//turns off the fruit if its life time is expaird
		if (fruit->getTimeOfLife() <= numOfPacmanSteps && fruit->GetisExist() == true)
		{
			//delete the fruit
			gotoxy(fruit->getPos().getPositionX(), fruit->getPos().getPositionY());
			cout << Board1.GetCoordinate(fruit->getPos().getPositionX(), fruit->getPos().getPositionY());
			//turns off the fruit
			fruit->SetisExist(false);
			numOfStepsToFruit = 0;
		}
		if (!fruit->GetisExist() && numOfStepsToFruit == 0)
		{
			numOfStepsToFruit = rand() % 40 + 50;
			numOfPacmanSteps = 0;
		}
		else if (numOfStepsToFruit <= numOfPacmanSteps && !fruit->GetisExist())
		{
			fruit->relife(Board1);
			numOfPacmanSteps = 0;
		}
	}
	
	
}

//scans all 'screen' type files
void GameManager::getFilesNames()
{
	std::string temp;

	for (const auto& p : std::filesystem::directory_iterator("."))
	{
		//push all the files that their type is 'screen'
		if (p.path().string().ends_with(".screen"))
		{
			temp = p.path().string();
			temp.erase(0, 2);
			filenames.push_back(temp);
		}
	}

	//sort the files in lexicographical order 
	std::sort(filenames.begin(), filenames.end());
}

Creature** GameManager::getcreatureArr()
{
	return arrCreature;
}

//set creature arr after reading screen from file
void GameManager::setCreature()
{
	numOfGhost = Board1.getNumOfGhost();
	for (int i = 0; i < 2 + numOfGhost; i++)
	{
		switch (i)
		{
		case PACMAN_TYPE:
			arrCreature[i] = new Pacman(Board1.getCreaturePos(i).getPositionY(), Board1.getCreaturePos(i).getPositionX());
			arrCreature[i]->setNumOfLines(Board1.getNumOfLines());
			arrCreature[i]->setSizeOfLine(Board1.getSizeOfLine());
			break;
		case FRUIT_TYPE:
			arrCreature[i] = new Fruit();
			arrCreature[i]->setNumOfLines(Board1.getNumOfLines());
			arrCreature[i]->setSizeOfLine(Board1.getSizeOfLine());
			break;

		default:
			arrCreature[i] = new Ghost(Board1.getCreaturePos(i).getPositionY(), Board1.getCreaturePos(i).getPositionX());
			arrCreature[i]->setNumOfLines(Board1.getNumOfLines());
			arrCreature[i]->setSizeOfLine(Board1.getSizeOfLine());
			break;
		}
	}
}

