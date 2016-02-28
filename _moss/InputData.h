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
#include "QBert_Cube.h"
#include "QBert_Cube_QBert.h"
#include "QBert_Cube_Monster.h"
#include "QBert_Cube_Item.h"

#ifndef H_INPUT_DATA
#define H_INPUT_DATA

//define class here
class InputData{
//public methods
public:
	vector<QBert_Cube> cubeList;
	QBert_Cube_QBert QBert;
	vector<QBert_Cube_Monster> monsterList;
	vector<QBert_Cube_Item> itemList;
	vector<int> checkCubeState;
	QBert_Cube_Item screenGround;
	QBert_Cube_Item cry;
	QBert_Cube_Item spin1;
	QBert_Cube_Item spin2;
	QBert_Cube_Item* scoreboard;
	QBert_Cube_Item liveNumber;
	QBert_Cube_QBert* QBertLives;

	QBert_Cube_Item opoeningBack; 
	QBert_Cube_Item openingStart;
	QBert_Cube_Item openingExit;
	QBert_Cube_Item openingButton;

	QBert_Cube_Item transBack; 
	QBert_Cube_Item transSign;


	QBert_Cube_Monster transMon1;
	QBert_Cube_Monster transMon2;
	QBert_Cube_Monster transMon3;

	QBert_Cube_Item endingBack; 
	QBert_Cube_Item endingSign;


};

#endif