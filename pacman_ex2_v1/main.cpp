//ID_1: 322437815
//ID_2: 208930586
#include <iostream>
#include "LoadMode.h"
#include "SaveMode.h"
#include "SilentMode.h"

using std::string;
using std::cout;
using std::cin;
enum Mode { SIMPLE, SAVE, SILENT, LOAD, UNKNOWN };

int getTheMode(char* argv);

int main(int argc, char** argv)
{
	hideCursor();
	SimpleMode* simplePtr;
	SaveMode* savePtr;
	LoadMode* loadPtr;
	SilentMode* silentPtr;
	int mode;
	if (argc > 1) mode = getTheMode(argv[1]);
	else mode = SIMPLE;
	switch (mode)
	{
	case SIMPLE:
		simplePtr = new SimpleMode;
		simplePtr->run();
		delete(simplePtr);
		break;
	case SAVE:
		savePtr = new SaveMode;
		savePtr->run();
		delete(savePtr);
		break;
	case SILENT:
		silentPtr = new SilentMode;
		silentPtr->run();
		delete(silentPtr);
		break;
	case LOAD:
		loadPtr = new LoadMode;
		loadPtr->run();
		delete(loadPtr);
		break;
	default:
		std::cout << "Invalid mode" << std::endl << std::endl;
		break;
	}
	return 0;
}

int getTheMode(char* argv)
{
	if (strcmp(argv, "-load") == 0)
		return LOAD;
	else if (strcmp(argv, "-save") == 0)
		return SAVE;
	else if (strcmp(argv, "-load[-silent]") == 0)
		return SILENT;
	else return UNKNOWN;
}