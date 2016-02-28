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

// tags to avoid duplicated include
#ifndef H_QBERT_CUBE
#define H_QBERT_CUBE

//define class here
class QBert_Cube{
//public methods
public:
	int index;
	int numberOfTriangle;
	vec3 centerPosition;
	GLfloat* vertexArray;
	GLfloat* colorArray;
	vec3 colorTop;
	vec3 colorBottom;
	vec3 colorLeft;
	vec3 colorRight;
	vec3 colorBack;
	vec3 colorFront;
	mat4 translation;
	int currentIndex;


	QBert_Cube();
	void setColor_Back(vec3 newColor);
	void setColor_Front(vec3 newColor);
	void setColor_Top(vec3 newColor);
	void setColor_Bottom(vec3 newColor);
	void setColor_Left(vec3 newColor);
	void setColor_Right(vec3 newColor);
	void updateColor();
	void setTranlation(float x_shift, float y_shift, float z_shift);
};

#endif