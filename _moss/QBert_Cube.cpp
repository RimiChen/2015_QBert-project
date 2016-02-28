#include "QBert_Cube.h"



QBert_Cube::QBert_Cube(){

	//vertex_buffer_data = new GLfloat[NumberOfTriangle*VertexPerTriangle*3+36*(HierachyTree.size()-1)];
	vertexArray = new GLfloat[12* 3 * 3];
	colorArray = new GLfloat[12* 3 * 3];
	currentIndex = 0;
	numberOfTriangle = 12;

	//Back red
	setColor_Back(vec3(1.0f, 0.0f, 0.0f));
	//Front green
	setColor_Front(vec3(0.0f, 1.0f, 0.0f));
	//Top blue
	setColor_Top(vec3(0.0f, 0.0f, 1.0f));
	//Bottom yellow
	setColor_Bottom(vec3(1.0f, 1.0f, 0.0f));
	//Left Magenta
	setColor_Left(vec3(1.0f, 0.0f, 1.0f));
	//Right cyan
	setColor_Right(vec3(0.0f, 1.0f, 1.0f));


	GLfloat tempVertexArray[] = 
	{ 
    //  X     Y     Z 
    // bottom
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,

    // top
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,

    // front
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,

    // back
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,

    // left
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,

    // right
     1.0f,-1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
	};

	memcpy( vertexArray, tempVertexArray, sizeof( tempVertexArray ) );

	GLfloat tempColorArray[] = 
	{ 
    //  R     G     B 
    // bottom
	colorBottom.r, colorBottom.g, colorBottom.b,
    colorBottom.r, colorBottom.g, colorBottom.b,
	colorBottom.r, colorBottom.g, colorBottom.b,
	colorBottom.r, colorBottom.g, colorBottom.b,
	colorBottom.r, colorBottom.g, colorBottom.b,
	colorBottom.r, colorBottom.g, colorBottom.b,


    // top
	colorTop.r, colorTop.g, colorTop.b,
    colorTop.r, colorTop.g, colorTop.b,
	colorTop.r, colorTop.g, colorTop.b,
	colorTop.r, colorTop.g, colorTop.b,
	colorTop.r, colorTop.g, colorTop.b,
	colorTop.r, colorTop.g, colorTop.b,


    // front
	colorFront.r, colorFront.g, colorFront.b,
    colorFront.r, colorFront.g, colorFront.b,
	colorFront.r, colorFront.g, colorFront.b,
	colorFront.r, colorFront.g, colorFront.b,
	colorFront.r, colorFront.g, colorFront.b,
	colorFront.r, colorFront.g, colorFront.b,


    // back
	colorBack.r, colorBack.g, colorBack.b,
    colorBack.r, colorBack.g, colorBack.b,
	colorBack.r, colorBack.g, colorBack.b,
	colorBack.r, colorBack.g, colorBack.b,
	colorBack.r, colorBack.g, colorBack.b,
	colorBack.r, colorBack.g, colorBack.b,

    // left
	colorLeft.r, colorLeft.g, colorLeft.b,
    colorLeft.r, colorLeft.g, colorLeft.b,
	colorLeft.r, colorLeft.g, colorLeft.b,
	colorLeft.r, colorLeft.g, colorLeft.b,
	colorLeft.r, colorLeft.g, colorLeft.b,
	colorLeft.r, colorLeft.g, colorLeft.b,


    // right
	colorRight.r, colorRight.g, colorRight.b,
    colorRight.r, colorRight.g, colorRight.b,
	colorRight.r, colorRight.g, colorRight.b,
	colorRight.r, colorRight.g, colorRight.b,
	colorRight.r, colorRight.g, colorRight.b,
	colorRight.r, colorRight.g, colorRight.b,
	};
	memcpy( colorArray, tempColorArray, sizeof( tempColorArray ) );
	
	translation = glm::mat4(1.0f);

}

void QBert_Cube::setColor_Back(vec3 newColor){
	colorBack = newColor;
	//updateColor();
	int shift = 6;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j<3; j++){
			colorArray[(i+shift)*9 +j*3 +0] = colorBack.r;
			colorArray[(i+shift)*9 +j*3 +1] = colorBack.g;
			colorArray[(i+shift)*9 +j*3 +2] = colorBack.b;
		}
	}
}
void QBert_Cube::setColor_Front(vec3 newColor){
	colorFront = newColor;
	//updateColor();
	int shift = 4;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j<3; j++){
			colorArray[(i+shift)*9 +j*3 +0] = colorFront.r;
			colorArray[(i+shift)*9 +j*3 +1] = colorFront.g;
			colorArray[(i+shift)*9 +j*3 +2] = colorFront.b;
		}
	}
}
void QBert_Cube::setColor_Top(vec3 newColor){
	colorTop = newColor;
	//updateColor();
	int shift = 2;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j<3; j++){
			colorArray[(i+shift)*9 +j*3 +0] = colorTop.r;
			colorArray[(i+shift)*9 +j*3 +1] = colorTop.g;
			colorArray[(i+shift)*9 +j*3 +2] = colorTop.b;
		}
	}

}
void QBert_Cube::setColor_Bottom(vec3 newColor){
	colorBottom = newColor;
	//updateColor();
	int shift = 0;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j<3; j++){
			colorArray[(i+shift)*9 +j*3 +0] = colorBottom.r;
			colorArray[(i+shift)*9 +j*3 +1] = colorBottom.g;
			colorArray[(i+shift)*9 +j*3 +2] = colorBottom.b;
		}
	}
}
void QBert_Cube::setColor_Left(vec3 newColor){
	colorLeft = newColor;
	//updateColor();
	int shift = 8;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j<3; j++){
			colorArray[(i+shift)*9 +j*3 +0] = colorLeft.r;
			colorArray[(i+shift)*9 +j*3 +1] = colorLeft.g;
			colorArray[(i+shift)*9 +j*3 +2] = colorLeft.b;
		}
	}
}
void QBert_Cube::setColor_Right(vec3 newColor){
	colorRight = newColor;
	//updateColor();
	int shift = 10;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j<3; j++){
			colorArray[(i+shift)*9 +j*3 +0] = colorRight.r;
			colorArray[(i+shift)*9 +j*3 +1] = colorRight.g;
			colorArray[(i+shift)*9 +j*3 +2] = colorRight.b;
		}
	}
}
void QBert_Cube::setTranlation(float x_shift, float y_shift, float z_shift){
	translation = glm::translate ( mat4(), vec3 (x_shift, y_shift, z_shift));
	centerPosition = vec3 (x_shift, y_shift, z_shift);
}
void QBert_Cube::updateColor(){
	GLfloat tempColorArray[] = 
	{ 
    //  R     G     B 
    // bottom
	colorBottom.r, colorBottom.g, colorBottom.b,
    colorBottom.r, colorBottom.g, colorBottom.b,
	colorBottom.r, colorBottom.g, colorBottom.b,
	colorBottom.r, colorBottom.g, colorBottom.b,
	colorBottom.r, colorBottom.g, colorBottom.b,
	colorBottom.r, colorBottom.g, colorBottom.b,


    // top
	colorTop.r, colorTop.g, colorTop.b,
    colorTop.r, colorTop.g, colorTop.b,
	colorTop.r, colorTop.g, colorTop.b,
	colorTop.r, colorTop.g, colorTop.b,
	colorTop.r, colorTop.g, colorTop.b,
	colorTop.r, colorTop.g, colorTop.b,


    // front
	colorFront.r, colorFront.g, colorFront.b,
    colorFront.r, colorFront.g, colorFront.b,
	colorFront.r, colorFront.g, colorFront.b,
	colorFront.r, colorFront.g, colorFront.b,
	colorFront.r, colorFront.g, colorFront.b,
	colorFront.r, colorFront.g, colorFront.b,


    // back
	colorBack.r, colorBack.g, colorBack.b,
    colorBack.r, colorBack.g, colorBack.b,
	colorBack.r, colorBack.g, colorBack.b,
	colorBack.r, colorBack.g, colorBack.b,
	colorBack.r, colorBack.g, colorBack.b,
	colorBack.r, colorBack.g, colorBack.b,

    // left
	colorLeft.r, colorLeft.g, colorLeft.b,
    colorLeft.r, colorLeft.g, colorLeft.b,
	colorLeft.r, colorLeft.g, colorLeft.b,
	colorLeft.r, colorLeft.g, colorLeft.b,
	colorLeft.r, colorLeft.g, colorLeft.b,
	colorLeft.r, colorLeft.g, colorLeft.b,


    // right
	colorRight.r, colorRight.g, colorRight.b,
    colorRight.r, colorRight.g, colorRight.b,
	colorRight.r, colorRight.g, colorRight.b,
	colorRight.r, colorRight.g, colorRight.b,
	colorRight.r, colorRight.g, colorRight.b,
	colorRight.r, colorRight.g, colorRight.b,
	};
	memcpy( colorArray, tempColorArray, sizeof( tempColorArray ) );	
}