/*===============
standrad library
=================*/
#include "standard_library.h"

/*===============
3rd party library
=================*/
#include "3rd_party.h";

/*=====================
self-defined structures
=======================*/
#include "self_defined_structures.h"

#ifndef H_GAME_STATUS
#define H_GAME_STATUS

//define class here
class GameStatus{
//public methods
public:
	int printCry;
	int gameLevel;
	int score;
	int digits[5];
	int lives;
	int gameRoom;
	int printEnd;

	void updateNumber();
};

#endif