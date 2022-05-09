#include "Menu.h"

using std::cout;
using std::endl;
using std::cin;
using std::getchar;
using std::string;

int Menu::getChoosesSingleScreen()
{
	return numOfBoard;
}

//func print menu and save the user selections
void Menu::printMenu(const vector <string> &fileNames)
{
	cout << "Menu: " << endl << "(1) Start black and white game\n(2) start colorful game" << endl;
	cout << "(8) Present instructions and keys\n(9) EXIT" << endl;
	setUser_choice();
	if (user_choice != 9)
	{
		chooseLevel();
		methodGame(fileNames);
	}

}

//print the first menu
//set colorful game if user ask for
void Menu::setUser_choice()
{
	bool flag = false, allReadyApper = false;
	user_choice = -1;
	while (user_choice != 1 && user_choice != 2 && user_choice != 8 && user_choice != 9)
	{ 
		if (flag == true && allReadyApper == false)
		{
			cout << "wrong key!" << endl;
			allReadyApper = true;
		}
		user_choice = _getch() - int('0');
		flag = true;
	}
	switch (user_choice)
	{
	case BLACK_AND_WHITE:
		break;
	case COLORFUL:
		setColorful(user_choice);
		break;
	case INSTRUCTIONS:
		printStructions();
		break;
	case EXIT:
		system("CLS");
		break;
	default:
		cout << "Error - Game failuer";
		exit(1);
	}

}

int Menu::getUser_choice() const
{
	return user_choice;
}

int Menu::getMethodGame() const
{
	return method_game;
}

void Menu::setColorful(int num)
{
	if (num > 0)
		colorful = true;
	else
		colorful = false;
}

//print the method options and saves the user selections
void Menu::methodGame(const vector <string>& fileNames)
{
	int i = 1;
	bool flag = false, allReadyApper = false;
	method_game = -1;
	numOfBoard = -1;
	system("CLS");
	cout << "Choose your game: " << endl << "(1) all screens in arow\n(2) choose single screen" << endl;
	while (method_game != ALL_SCREEN && method_game != SINGLE_SCREEN)
	{
		if (flag == true && allReadyApper == false)
		{
			cout << "wrong key!" << endl;
			allReadyApper = true;
		}
		method_game = _getch() - int('0');
		flag = true;
	}
	switch (method_game)
	{
	case ALL_SCREEN:
		numOfBoard = 1;
		break;
	case SINGLE_SCREEN:
		system("CLS");
		cout << "Choose a screen: " << endl;
		flag = false, allReadyApper = false;
		for (const auto& p : fileNames)
		{
			cout << i << ". " << p << '\n';
			i++;
		}
		while (numOfBoard > i || numOfBoard < 1)
		{
			if (flag == true && allReadyApper == false)
			{
				cout << "wrong key!" << endl;
				allReadyApper = true;
			}
			numOfBoard = _getch() - int('0');
			flag = true;
		}
		break;
	default:
		cout << "Error - Game failuer";
		return;
	}
}

void Menu::setNumOfBoard(const int num)
{
	numOfBoard = num;
}

bool Menu::getColorful() const
{
	return colorful;
}

void Menu::printStructions()
{
	char key;
	system("CLS");
	cout << "instructions:\n\n"
		"The player controls Pac-Man, who must eat all the dots inside an enclosed maze\n"
		"while avoiding two ghosts.\n\n"
		"Pacman has 3 lives. "
		"If the life ends, the player loses.\n\n"
		"If the player manages to eat all the bread crumbs he wins.\n\n"
		"Keys: \nUp-'w'/'W'\nDown-'x'/'X'\nLeft-'a'/'A'\nRight-'d'/'D'\nStay- 's'/'S'\n\n"
		"There are to options to play: "
		"press any key to continue";

	key = getchar();
	system("CLS");
}

void Menu::setGhostLevel(const int level)
{
	ghostLevel = level;
}


int Menu::getGhostLevel() const
{
	return ghostLevel;
}

void Menu::chooseLevel()
{
	bool flag = false, allReadyApper = false;
	ghostLevel = -1;
	system("CLS");
	cout << "Choose your game level: " << endl << "(1) novice\n(2) good\n(3) best" << endl;
	while (ghostLevel != NOVICE && ghostLevel != GOOD&& ghostLevel !=BEST)
	{
		if (flag == true && allReadyApper == false)
		{
			cout << "wrong key!" << endl;
			allReadyApper = true;
		}
		ghostLevel = _getch() - int('0');
		flag = true;
	}
}
