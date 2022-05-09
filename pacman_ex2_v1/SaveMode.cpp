#include "SaveMode.h"
#include <fstream>

using std::endl;
using std::ofstream;
using std::ios;
void SaveMode::run()
{
	static bool allReadyLoad = false;
	//prevents reloading
	if (!allReadyLoad)
	{
		allReadyLoad = true;
		getFilesNames();
	}

	searchLogFiles();
	//switch case by user choice
	do
	{
		//print menu and updates board's names in 'filenames' vector
		menu.printMenu(getStringFiles());
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
		system("CLS");
		cout << "Note!" << endl << "another test in a row might yield incorrect result!" << endl << endl;
	} while (menu.getUser_choice() != EXIT);
	system("CLS");
	cout << "good bye" << endl << endl;
}

//starts a single game
bool SaveMode::startGame()
{
	bool haveMoreLife = true;
	char key = 0;
	loadBoardData();
	string fileWrite = buildFileNameSteps(string(".steps"));
	ofstream stepOutFile(fileWrite, ios::trunc);
	string fileWrite2 = buildFileNameSteps(string(".res"));
	ofstream resOutFile(fileWrite2, ios::trunc);
	do
	{
		if (_kbhit())
		{
			key = _getch();
			setPacmanDir(key);
		}
		movePacman(true, colorful);
		Sleep(100/getGhostLevel());
		stepOutFile << "Pac:" << dir[getcreatureArr()[0]->getDir()] << "_";
		printScore();
		if (getNumOfLife() < 1) haveMoreLife = false;
		updateResToFile(resOutFile, eat());
		if (!haveMoreLife) break;
		if (pacmanMoove == true)
		{
			SimpleMode::moveAllCreaturs(true, colorful);
			PrintCreatureStepsToFile(stepOutFile);
			printLife();
			if (getNumOfLife() < 1) haveMoreLife = false;
			updateResToFile(resOutFile, eat());
			if (!haveMoreLife) break;
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
		if (getScore() == getMaxScore()) break;
	} while (key != -1);
	printResToFile(resOutFile, haveMoreLife);
	stepOutFile.close();
	resOutFile.close();
	return haveMoreLife;
}

//loads Board Data after the file has been read
void SaveMode::loadBoardData()
{
	system("CLS");
	setCreature();
	GhostsetLevel();
	getBoard().printBoard(menu.getColorful());
	printlegend();
}

//checks for logs file
//note the user in case it find
void SaveMode::searchLogFiles()
{
	for (const auto& p : std::filesystem::directory_iterator("."))
	{
		//push all the files that their type is 'screen'
		if (p.path().string().ends_with(".steps") || p.path().string().ends_with(".res"))
		{
			system("CLS");
			cout << "Note!" << endl << "You already have files of type: steps/res (logs) in the game folder. keeping this files might yield incorrect result!" << endl;
			Sleep(7000);
			system("CLS");
			return;
		}
	}
}


//returns the name of 'screen' type file
string SaveMode::buildFileNameSteps(string type)
{
	string res = getStringFiles()[getCurrBoard() - 1];
	for (char a: "screen")
	{
		res.pop_back();
	}
	res += type;
	return res;
}

//// we are here!!!!!!!!
void SaveMode::updateResToFile(ofstream& resOutFile, bool eaten)
{
	if (eaten) resOutFile << "Pac died:" << getGameCounter() << "\n";
}

void SaveMode::PrintCreatureStepsToFile(std::ofstream& stepsOutFile)
{
	int num = getGameNumOfGhosts() + 1;
	static bool flag = false;
	Fruit* fruit = NULL;
	for (int j = 1; j <= num; j++)
	{
		switch (j)
		{
		case 1:
			fruit = dynamic_cast<Fruit*>(getCreatureArrFromGameManager()[j]);
			if (fruit)
				if (fruit->GetisExist())
				{
					stepsOutFile << "Fruit:live," << fruit->getValue();
					if(!flag)
						stepsOutFile << ',' << fruit->getPos().getPositionX() << "-" << fruit->getPos().getPositionY();
					stepsOutFile << ",dir:" << dir[fruit->getDir()] << "_";
					flag = true;
				}
				else
				{
					stepsOutFile << "Fruit:dead" << "_";
					flag = false;
				}
			break;
		default:
			stepsOutFile << "Ghost" << j << ":" << dir[getCreatureArrFromGameManager()[j]->getDir()] << "_";
			break;
		}
	}
}

void SaveMode::printResToFile(std::ofstream& resOutFile, bool isFinish)
{
	resOutFile << getStringFiles()[getCurrBoard() - 1] << " life's:" << getLife() << '\n';
	if(isFinish) resOutFile << getStringFiles()[getCurrBoard() - 1] << " finish at:" << getCounter() << '\n';
}

