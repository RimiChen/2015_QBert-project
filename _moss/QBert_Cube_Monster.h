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
//#include "InputData.h"

// tags to avoid duplicated include
#ifndef H_QBERT_CUBE_MONSTER
#define H_QBERT_CUBE_MONSTER

//define class here
class QBert_Cube_Monster{
//public methods
public:
	int monsterIndex;
	int monsterType;
	int numberOfTriangle;
	GLfloat* vertexArray;
	GLfloat* colorArray;
	GLfloat* uvArray;
	GLfloat* constantArray;

	vec3 colorTop;
	vec3 colorBottom;
	vec3 colorLeft;
	vec3 colorRight;
	vec3 colorBack;
	vec3 colorFront;
	mat4 translation;
	mat4 scaleMatrix;
	mat4 rotateMatrix;
	int startIndex;
	vec3 currentPosition;
	int currentIndex;
	int textureBaseNumber;
	//int usedList;


	QBert_Cube_Monster();
	void setColor_Back(vec3 newColor);
	void setColor_Front(vec3 newColor);
	void setColor_Top(vec3 newColor);
	void setColor_Bottom(vec3 newColor);
	void setColor_Left(vec3 newColor);
	void setColor_Right(vec3 newColor);
	void updateColor();
	void setTranlation(float x_shift, float y_shift, float z_shift);
	void setScale(float x_scale, float y_scale, float z_scale);
	// only y rotate
	void setRotate(float radius);
	void setAllColor(vec3 newColor);
	void resetStartPosition(int random, int currentCubeTotal, vector<QBert_Cube> cubeList, vector<int> usedList);
	bool checkPosition(int index, vector<QBert_Cube> input,  int currentCubeTotal, vector<int> usedList);
	vec3 randomMove(int direction,vector<QBert_Cube> cubeList, int currentCubeTotal);
	bool checkOut(vector<QBert_Cube> cubeList, vec3 position, int currentCubeTotal);
	int updateCurrentPosition();
	int getIndex(vector<QBert_Cube> cubeList, vec3 position, int currentCubeTotal);
	void setBaseNumber(int baseNumber);
};

#endif