#pragma once
#include "GameManager.h"

class SilentMode : virtual public GameManager
{
public:
	void run() override;
	virtual bool startGame(string stepsItr, string resItr);
	bool getFilesNamesByType();
	void readingFilesFailerMassege();
	bool checkForMissingFiles();
	void readOneWordFromFile(int& creature, int& step, std::ifstream& stepFile);
	void rebuildWord(string str, int& res, bool& flag);
	bool checkIfGotEatenOnTime(std::ifstream& resFile);
	void testStatusMassage(bool status);
	bool checkIfResIsMatching(std::ifstream& resFile, string name, int res);
	vector<string> getResFilenames();
	vector <string> getStepsFilenames();
	void setFruitPosAndValue(std::ifstream& stepFile);

private:
	vector <string> resFilenames;
	vector <string> stepsFilenames;
};
