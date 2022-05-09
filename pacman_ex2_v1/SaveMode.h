#pragma once

#include "SimpleMode.h"

class SaveMode : public SimpleMode
{
public:
	//SaveMode();
	bool startGame() override;
	void run() override;
	string buildFileNameSteps(string type);
	void updateResToFile(std::ofstream &resOutFile, bool eaten);
	void PrintCreatureStepsToFile(std::ofstream& resOutFile);
	void printResToFile(std::ofstream& resOutFile, bool isFinish);
	void searchLogFiles();
	void loadBoardData();

private:
	vector<string> dir = { "STOP", "UP", "DOWN", "LEFT", "RIGHT" };
};
