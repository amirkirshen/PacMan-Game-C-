#pragma once

//ID_1: 322437815
//ID_2: 208930586


#include "Creature.h"

class Fruit : public Creature
{
private:
	int value = 5;
	int time_of_life = 10;	//max steps the fruit makes until it death
	int num_of_steps = 0;	 
	bool isExist = false;


public:
	Fruit(const int _x, const int _y, const int _dir, Board &board, const int _color = WHITE, int value = 5);
	Fruit();
	int getValue() const;
	void setValue(const int newVal);
	void randomFruit();
	void randomPos(Board &board);
	void move(Board &board, int dir = -1, bool colorful = false); //if dir is 0 so random mode is activated
	void moveAndDraw(Board& board, int dir, bool colorful);
	void draw(int old_x, int old_y, Board &board, bool colorful) const;
	void reset()override;
	void SetisExist(bool exp);
	bool GetisExist() const;
	void relife(Board& board);
	int getTimeOfLife() const;

};