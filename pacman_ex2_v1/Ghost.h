#pragma once
//ID_1: 322437815
//ID_2: 208930586

#include "Creature.h"
#include <queue>
using std::queue;
using std::vector;

class Ghost: public Creature
{
public:
	Ghost(const int x, const int y, const int _dir = 0, const int _color = WHITE);
	Ghost();
	bool move(Board &board, int dir, position pacPos, bool colorful = false, bool _isSmart = false);
	void chooseDir(Board& board, position pacPos, const bool flag);
	//void moveSmart(Board &board, position pacPos);
	void smartDirMove(Board &board, position pacPos);
	//void draw(int old_x, int old_y, Board &board) const;
	bool isValidStep(const vector<vector<bool>>&, int &row, int &col, Board &board);
	bool isValidStep(int row, int col, Board& board);
	position BFS(Board &board, vector<vector<bool>> visit, int row, int col);
	void reset()override;
	void setLevel(const int num);
	void moveRandom(Board board, int& numOfRandomMoves, int num);
	void LegalmoveRandom(Board board, int& numOfRandomMoves);
	position nextStep(int dir);
	bool getIsSmart() { return isSmart; };
	void moveAndDraw(Board& board, int dir, position pacPos, bool colorful, bool isSmart);

private:
	position original;
	int level = NOVICE;
	bool isSmart = true;    //calculate shortest way once in 2 moves
};
