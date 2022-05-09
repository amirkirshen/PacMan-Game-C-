//ID_1: 322437815
//ID_2: 208930586
#include "board.h"
#include "Utilities.h"


using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ios;
using std::getline;



Board::Board()
{
	cleanBoard();
}


void Board::cleanBoard()
//clean board
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL + 1; j++)
		{
			gameBoard_1[i][j] = ' ';
			boolMatrix[i][j] = false;
		}
	}
	maxScorePerBoard = 0;
	num_of_lines = 0;
	size_of_line = 0;
	num_of_ghost = 0;
}

void Board::reset(string boardName)
//initalize the matrix and inserts walls
{
	cleanBoard();
	maxScorePerBoard = 0;
	readBoard(boardName);
}

void Board::reset()
//initalize the matrix but not read a new one
{
	cleanBoard();
	maxScorePerBoard = 0;
}


void Board::readBoard(string boardName)
//read the board from the file 'boardName'
{
	int size = 0, j = 0;
	char ch = '_';
	num_of_ghost = 0;
	num_of_pacman = 0;
	num_of_lines = 0;
	size_of_line = 0;

	//open the file
	fstream board1(boardName, ios::in);
	if (!board1)
	{
		cout << "file should not be opened!" << endl;
		exit(1);
	}
	readFirstLine(board1);	//main goal - calculate the size of the first line
	num_of_lines++;
	
	//insert all the board to matrix
	while (!board1.eof())
	{
		for (int i = 0; i < size_of_line /*&& !board1.eof()*/; i++)
		{
			board1 >> std::noskipws >> ch;
			gameBoard_1[num_of_lines][i] = ch;
			rebuildBoard(num_of_lines, i);
			if (ch == '\n')	break;
		}
		num_of_lines++;
	}
	gameBoard_1[num_of_lines - 1][size_of_line - 1] = '\n';
	board1.close();
	isValidBoard(boardName);
}

//return the num of bread crumb on the board
int Board::getMaxScore()
{
	return maxScorePerBoard;
}

void Board::readFirstLine(fstream& board1)
//read first line to set the size of line
{
	char ch;
	bool flag = false;

	do
	{
		board1 >> std::noskipws >> ch;
		gameBoard_1[num_of_lines][size_of_line] = ch;
		rebuildBoard(num_of_lines, size_of_line);
		size_of_line++;
	} while (ch != '\n' && size_of_line < 82);
	
	//incase that the firstLine is longer than 80 chars ('\n' not counting)
	if (size_of_line == 82)
	{
		size_of_line--;
		gameBoard_1[num_of_lines][size_of_line - 1] = '\n';
	}
}

void Board::rebuildBoard(int& row, int& col)
//update the board to official game chars
{
	int num_of_line_txt = 0;
	switch (gameBoard_1[row][col])
	{
	case '@':
		gameBoard_1[row][col] = ' ';
		posArr[0].setposition(row, col);
		boolMatrix[row][col] = true;
		num_of_pacman++;
		break;
	case '#':
		gameBoard_1[row][col] = BOUNDARY;
		break;
	case '$':
		num_of_ghost++;
		gameBoard_1[row][col] = FOOD;
		maxScorePerBoard++;
		posArr[1 + num_of_ghost].setposition(row, col);
		boolMatrix[row][col] = true;
		break;
	case 't':
		gameBoard_1[row][col] = TUNNEL;
		break;
	case '&':
		gameBoard_1[row][col] = 'A';
		ampersand_appeard = true;
		x_ampersand_pos = row;
		y_ampersand_pos = col;
		num_of_line_txt++;
		break;
	case ' ':
		gameBoard_1[row][col] = FOOD;
		boolMatrix[row][col] = true;
		maxScorePerBoard++;
		break;
	case '\t':
		for (int i = 0; i < 4; i++)
		{
			col += i;
			gameBoard_1[row][col] = FOOD;
			boolMatrix[row][col] = true;
			maxScorePerBoard++;
		}
		break;
	case '%':
		gameBoard_1[row][col] = ' ';
		break;
	default:
		break;
	}
}

bool Board::isValidBoard(string boardName)
{
	bool flag = true;

	system("CLS");
	cout << endl << endl;
	if (num_of_pacman != 1)
	{
		cout << "We found " << num_of_pacman << " pacman's on the " << boardName << " while only one is allowed" << endl;
		flag = false;
	}
	if (num_of_ghost < 1 || num_of_ghost > 4)
	{
		cout << "We found " << num_of_ghost << " on the " << boardName << " while only 1-4 are allowed" << endl;
		flag = false;
	}


	if (!flag)
	{
		gotoxy(0, 0);
		cout << "Invalid board!!";
	}
	return flag;
}

void Board::printBoard(bool colorful)
//print the board and the data bar
const
{
	int j = 0;
	for (int i = 0; i < num_of_lines; i++)
	{
		for (int j = 0; j < size_of_line + 1; j++)
		{
			if (gameBoard_1[i][j] == BOUNDARY && colorful)
				setTextColor(wallsColor);
			cout << gameBoard_1[i][j];
			if (gameBoard_1[i][j] == BOUNDARY && colorful)
				setTextColor(WHITE);
			if (gameBoard_1[i][j] == '\n') break;

		}
	}
	if (colorful)setTextColor(WHITE);
}

void Board::verticalWall(int x, int y, int length)
//insert vertial wall: (x,y)- starting point, length - length of the wall
{
	for (int i = 0; i < length; i++)
	{
		gameBoard_1[x + i][y] = BOUNDARY;
	}
}

void Board::horizontal(int x, int y, int length)
//insert horizontal wall: (x,y)- starting point, length - length of the wall
{
	for (int i = 0; i < length; i++)
	{
		gameBoard_1[x][y + i] = BOUNDARY;
	}
}

char Board::GetCoordinate(int x, int y) const
//return the coordinate in gameBoard
{
	return gameBoard_1[y][x];
}

bool Board::GetBoolCoordinate(int x, int y) const
{
	return boolMatrix[y][x];
}



void Board::upDate(int x, int y, char ch)
{
	gameBoard_1[y][x] = ch;
}

void Board::setColor(int color)
{
	this->wallsColor = color;
}

int Board::getColor()const
{
	return(this->wallsColor);
}

void Board::readOneChar(fstream& board, char& ch)
{
	//read a char from file "board" and insert it to game_board
	//use for reading first line only - this func updates the sizeOfLine
	board >> std::noskipws >> ch;
	gameBoard_1[num_of_lines][size_of_line] = ch;
	rebuildBoard(num_of_lines, size_of_line);
	size_of_line++;
}

void Board::read19Chars(fstream& board)
//read 20 chars after '&'
//use for reading first line only - this func updates the sizeOfLine
{
	char temp;
	for (int i = 1; i < 20; i++)
	{
		readOneChar(board, temp);
	}
}

void Board::read21Chars(fstream& board)
//read 20 chars after '&'
//use for reading first line only - this func updates the sizeOfLine
{
	char temp;
	for (int i = 0; i < 21; i++)
	{
		readOneChar(board, temp);
	}
}

int Board::getNumOfLines()
{
	return num_of_lines;
}

int Board::getSizeOfLine()
{
	return size_of_line;
}

int Board::getNumOfGhost()
{
	return num_of_ghost;
}

position& Board::getCreaturePos(int i)
{
	return posArr[i];
}

position Board::getAmpersandPos() const
{
	return position(y_ampersand_pos, x_ampersand_pos);
}

