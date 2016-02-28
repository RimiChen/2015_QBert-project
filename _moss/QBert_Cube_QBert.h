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
#ifndef H_QBERT_CUBE_QBERT
#define H_QBERT_CUBE_QBERT

//define class here
class QBert_Cube_QBert{
//public methods
public:
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
	vec3 currentPosition;
	int currentIndex;


	QBert_Cube_QBert();
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
};

#endif