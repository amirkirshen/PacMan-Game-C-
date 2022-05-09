#pragma once
#include "SimpleMode.h"
#include "SilentMode.h"

class LoadMode : public SilentMode, public SimpleMode
{
public:
	bool startGame(string stepsScreen, string resScreen) override;
	void run() override;
	void moveOrCleanFruit(Fruit* fruitPtr);

private:
	
};
