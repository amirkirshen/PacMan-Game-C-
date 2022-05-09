#include "GameManager.h"
#include "SilentMode.h"
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

vector<string> SilentMode::getResFilenames()
{
	return resFilenames;
}
vector <string> SilentMode::getStepsFilenames()
{
	return stepsFilenames;
}

//starts the all game
void SilentMode::run()
{
	
	static bool allReadyLoad = false, testSucceed = true;

	//check that all the files are exist:
	//check for a res file that not mach steps file or oposite
	if (!getFilesNamesByType())
	{
		Sleep(600);
		system("CLS");
		cout << "we can't complete the test because of those missing files" << endl;
		cout << "please check that all the testing files are exist" << endl;
		return;
	}
	auto stepsItr = stepsFilenames.begin();
	auto resItr = resFilenames.begin();
	while (stepsItr != stepsFilenames.end() && resItr != resFilenames.end() && testSucceed)
	{
		string temp = resItr.operator*().substr(0, resItr.operator*().size() - 4);
		getBoard().cleanBoard();
		getBoard().readBoard(temp + ".screen");
		setMaxScore(getBoard().getMaxScore() + getMaxScore());
		setCreature();
		testSucceed = testSucceed && startGame(*stepsItr, *resItr);
		if (testSucceed)
		{
			stepsItr++;
			resItr++;
		}
	}
	testStatusMassage(!testSucceed);
}

//start a single game
bool SilentMode::startGame(string stepsScreen, string resScreen)
{
	ifstream stepFile, resFile;
	Creature* cretPtr = nullptr;
	stepFile.open(stepsScreen);
	resFile.open(resScreen);
	int dir, creature;
	bool isSucceed = true;
	while (!stepFile.eof() && getNumOfLife() > 0 && getScore() < getMaxScore())
	{
		readOneWordFromFile(creature, dir, stepFile);
		cretPtr = getcreatureArr()[creature];
		cretPtr->setDir(dir);
		Pacman* pacPtr = dynamic_cast<Pacman*>(cretPtr);
		if (pacPtr)
			pacPtr->move(getBoard(), getScoreByRef(), false, false);
		else
			cretPtr->move(getBoard(), false, false);
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
	if(getNumOfLife() != 0)isSucceed = isSucceed && checkIfResIsMatching(resFile, "screen finish at", getCounter());
	return isSucceed;
}

//prints if test has been secced or not
void SilentMode::testStatusMassage(bool status)
{
	system("CLS");
	if (status)
		cout << "test failed" << endl << endl;
	else
		cout << "test succeed" << endl << endl;
}

//checks for each board if it has res and steps files
//builds the names file vectors and call to "checkForMissingFiles" func
//returns answer
bool SilentMode::getFilesNamesByType()
{
	string resTemp, stepTemp;
	std::pair<string, string> temp;
	bool first = false, second = false;
	for (const auto& p : std::filesystem::directory_iterator("."))
	{
		//push all the files that their type is 'screen'
		if (p.path().string().ends_with(".res"))
		{
			resTemp = p.path().string();
			resTemp.erase(0, 2);
			resFilenames.push_back(resTemp);
		}
		else if (p.path().string().ends_with(".steps"))
		{
			stepTemp = p.path().string();
			stepTemp.erase(0, 2);
			stepsFilenames.push_back(stepTemp);
		}
	}
	if (!checkForMissingFiles()) return false;
	//sort the files in lexicographical order 
	std::sort(resFilenames.begin(), resFilenames.end());
	std::sort(stepsFilenames.begin(), stepsFilenames.end());

	return true;
}

//checks for each board if it has res and steps files
bool SilentMode::checkForMissingFiles()
{
	vector<string> resTemp;
	vector<string> stepsTemp;

	for (string str: resFilenames)
		resTemp.push_back(str.substr(0, str.size() - 4));

	for (string str2 : stepsFilenames)
		stepsTemp.push_back(str2.substr(0, str2.size() - 6));

	while (resTemp.size() != 0 && stepsTemp.size() != 0)
	{
		if (resTemp[0] != stepsTemp[0])
		{
			readingFilesFailerMassege();
			return false;
		}
		resTemp.erase(resTemp.begin());
		stepsTemp.erase(stepsTemp.begin());
	}
	if (resTemp.size() != 0 || stepsTemp.size() != 0)
	{
		readingFilesFailerMassege();
		return false;
	}
	return true;
}

void SilentMode::readingFilesFailerMassege()
{
	system("CLS");
	cout << "there are missing files - No match was found between the number of stepFiles and the number of resFiles" << endl;
	Sleep(6000);
}

//read one word and translate to creature and dir
void SilentMode::readOneWordFromFile(int& creature, int& step, ifstream& stepFile)
{
	char temp;
	int i = 0;
	string creatureStr, dirStr;
	Fruit* fruit = dynamic_cast<Fruit*>(getcreatureArr()[1]);
	static bool flag = false;
	stepFile >> temp;
	do
	{
		if (step == 6 && !flag)
		{
			setFruitPosAndValue(stepFile);
			flag = true;
		}
		while (temp != ':')
		{
			creatureStr += temp;
			stepFile >> temp;
		}
		if(step != 6) rebuildWord(creatureStr, creature, flag);
		stepFile >> temp; // skip ':'
		while (temp != '_' && temp != ',')
		{
			dirStr += temp;
			stepFile >> temp;
		}
		//stepFile >> temp; // skip '_'
		rebuildWord(dirStr, step, flag);
		dirStr = "";		//incase fruit is alive and it read again
		creatureStr = "";	//incase fruit is alive and it read again
	} while (step == 6);
}

//get a string and return creature place in arr or dir
void SilentMode::rebuildWord(string str, int& res, bool& flag)
{
	if (str.compare("Pac") == 0) {
		res = 0;
		raiseCounter();
	}
	else if (str.compare("Fruit") == 0) res = 1;
	else if (str.compare("Ghost2") == 0) res = 2;
	else if (str.compare("Ghost3") == 0) res = 3;
	else if (str.compare("Ghost4") == 0) res = 4;
	else if (str.compare("Ghost5") == 0) res = 5;
	else if (str.compare("STOP") == 0) res = 0;
	else if (str.compare("UP") == 0) res = 1;
	else if (str.compare("DOWN") == 0) res = 2;
	else if (str.compare("LEFT") == 0) res = 3;
	else if (str.compare("RIGHT") == 0) res = 4;
	else if (str.compare("dead") == 0) 
	{
		flag = false;
		Fruit* ptr = dynamic_cast<Fruit*>(getcreatureArr()[1]);
		if (ptr) ptr->SetisExist(false);
	}
	else if (str.compare("live") == 0)
	{
		res = 6;
		Fruit* ptr = dynamic_cast<Fruit*>(getcreatureArr()[1]);
		if (ptr) ptr->SetisExist(true);
	}
	//else // need to had a case that the program does not recognize the string
}

void SilentMode::setFruitPosAndValue(ifstream& stepFile)
{
	string tempstr;
	char temp;
	int x, y;
	bool flag = false;
	Fruit* ptr = dynamic_cast<Fruit*>(getcreatureArr()[1]);
	stepFile >> temp;
	if (ptr) ptr->setValue(int(temp) - int('0'));
	stepFile >> temp;
	for (int i = 0; i < 2; i++)
	{
		tempstr = "";
		stepFile >> temp;
		while (temp != '-' && temp != ',')
		{
			tempstr += temp;
			stepFile >> temp;
		}
		if (ptr)
		{
			if (!flag)
			{
				x = std::stoi(tempstr);
				flag = true;
			}
			else
				y = std::stoi(tempstr);
			if (i == 1)ptr->setPos(x, y);
		}
	}
}

//when eat() return true - call this func
//this func checks in res file if pacman died when it should
//returns true if got eaten as wrote - else returns false
bool SilentMode::checkIfGotEatenOnTime(ifstream& resFile)
{
	string resStatus;
	char temp;
	bool flag = false;
	for (int i = 0; i < 2; i++)
	{
		resFile >> temp;
		while (temp != ':' && temp != '\n' && !resFile.eof())
		{
			resStatus += temp;
			resFile >> std::noskipws >> temp;
		}
		if (!flag && resStatus.compare("Pac died") != 0) return false;
		else if (i != 0 && std::stoi(resStatus) != getCounter()) return false;
		flag = true;
		resStatus = "";
	}
	return true;
}

//check if scors or life are matchig to res file
bool SilentMode::checkIfResIsMatching(ifstream& resFile, string name, int res)
{
	string resStatus;
	char temp;
	bool flag = false;
	resFile >> temp;
	while (temp != ':' && !resFile.eof())
	{
		if (flag) resStatus += temp;
		if (temp == '.') flag = true;
		resFile >> std::noskipws >> temp;
	}
	resFile >> temp;
	if (resStatus.compare(name) == 0)
	{
		resStatus = "";
		while (temp != '\n' && !resFile.eof())
		{
			resStatus += temp;
			resFile >> std::noskipws >>temp;
		}
	}
	else
	{
		system("CLS");
		cout << "Corrupt file" << endl;
		Sleep(3000);
		return false;
	}
	if (std::stoi(resStatus) != res) return false;
	return true;
}
