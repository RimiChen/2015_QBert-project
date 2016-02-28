#include "QBert_Cube_Monster.h"



QBert_Cube_Monster::QBert_Cube_Monster(){

	//vertex_buffer_data = new GLfloat[NumberOfTriangle*VertexPerTriangle*3+36*(HierachyTree.size()-1)];
	vertexArray = new GLfloat[12* 3 * 3];
	colorArray = new GLfloat[12* 3 * 3];
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

/*
	 // front
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
*/

    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,

/* 
	// back
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
*/
    -1.0f,-1.0f, -1.0f,
     1.0f,-1.0f, -1.0f,
     1.0f, 1.0f, -1.0f,
	-1.0f,-1.0f, -1.0f,
     1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

/*
	// left
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
*/
     -1.0f,-1.0f, 1.0f,
     -1.0f,-1.0f,-1.0f,
     -1.0f, 1.0f,-1.0f,
     -1.0f,-1.0f, 1.0f,
     -1.0f, 1.0f,-1.0f,
     -1.0f, 1.0f, 1.0f,


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

	float textureIndex = textureBaseNumber;
	uvArray=new GLfloat[12*3*3];
	for(int i =0; i<6;i++){

		if(i==2){
			textureIndex = textureBaseNumber;
		}
		else{
			textureIndex = 0;
		}
		uvArray[i*18+0] = 0.0f;
		uvArray[i*18+1] = 1.0f;
		uvArray[i*18+2] = textureIndex; 

		uvArray[i*18+3] = 1.0f;
		uvArray[i*18+4] = 1.0f;
		uvArray[i*18+5] = textureIndex; 

		uvArray[i*18+6] = 1.0f;
		uvArray[i*18+7] = 0.0f;
		uvArray[i*18+8] = textureIndex; 

		uvArray[i*18+9] = 0.0f;
		uvArray[i*18+10] = 1.0f;
		uvArray[i*18+11] = textureIndex; 

		uvArray[i*18+12] = 1.0f;
		uvArray[i*18+13] = 0.0f;
		uvArray[i*18+14] = textureIndex; 

		uvArray[i*18+15] = 0.0f;
		uvArray[i*18+16] = 0.0f;
		uvArray[i*18+17] = textureIndex; 
	}

	constantArray=new GLfloat[12*3*3];
	for(int i =0; i<12*3;i++){
		constantArray[i*3+0] = 0.0f;
		constantArray[i*3+1] = 0.0f;
		constantArray[i*3+2] = 0; 
	}


	translation = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);

}

void QBert_Cube_Monster::setColor_Back(vec3 newColor){
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
void QBert_Cube_Monster::setColor_Front(vec3 newColor){
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
void QBert_Cube_Monster::setColor_Top(vec3 newColor){
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
void QBert_Cube_Monster::setColor_Bottom(vec3 newColor){
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
void QBert_Cube_Monster::setColor_Left(vec3 newColor){
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
void QBert_Cube_Monster::setColor_Right(vec3 newColor){
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
void QBert_Cube_Monster::setTranlation(float x_shift, float y_shift, float z_shift){
	translation = glm::translate ( mat4(), vec3 (x_shift, y_shift, z_shift));
	currentPosition =  vec3 (x_shift, y_shift, z_shift);
}
void QBert_Cube_Monster::setScale(float x_scale, float y_scale, float z_scale){
	scaleMatrix = glm::scale( mat4(), vec3 (x_scale, y_scale, z_scale));
}
	// only y rotate
void QBert_Cube_Monster::setRotate(float radius){
	rotateMatrix = glm::rotate(glm::mat4(), glm::radians(radius), glm::vec3(0,1,0));
}
void QBert_Cube_Monster::setAllColor(vec3 newColor){
	setColor_Back(newColor);
	setColor_Front(newColor);
	setColor_Top(newColor);
	setColor_Bottom(newColor);
	setColor_Left(newColor);
	setColor_Right(newColor);
}
void QBert_Cube_Monster::updateColor(){
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
void QBert_Cube_Monster::resetStartPosition(int random, int currentCubeTotal, vector<QBert_Cube> cubeList, vector<int> usedList){

	//cout << "---" << currentCubeTotal <<endl;
	startIndex = random;
	//cout<< "used list "<<usedList.size();
	//cout << "--- rand " << startIndex <<endl;
	while(checkPosition(startIndex, cubeList, currentCubeTotal, usedList)){
		startIndex = rand()%(currentCubeTotal-1)+1;
		//cout << "check " << random << endl;
	}
	currentIndex = startIndex;
	cout << "Monster start in cube " << startIndex << endl;
}
bool QBert_Cube_Monster::checkPosition(int index, vector<QBert_Cube> cubeList, int currentCubeTotal, vector<int> usedList){

	int i =0;
	int count = 0;
	vec3 objectPosition = cubeList[index].centerPosition;

	while (i < currentCubeTotal){
		//cout <<"checking cube " << input.cubeList[i].index << endl;
		if(objectPosition.x == cubeList[i].centerPosition.x && objectPosition.z == cubeList[i].centerPosition.z && cubeList[i].centerPosition.y -objectPosition.y >= 2){
			//cout<< "On cube " << i<< endl;
			return true;
		}
		else{
			i++;
		}
	}

	if(usedList.size()>0){
		for(int i =0; i < usedList.size(); i++){
			if(index == usedList[i]){
				return true;
			}
		}
	}
	if(index < 10){
		return true;
	}

	return false;

}
vec3 QBert_Cube_Monster::randomMove(int direction, vector<QBert_Cube> cubeList, int currentCubeTotal){
	vec3 nextPosition;
	vec3 resultPosition;

	if(monsterType == 0){
		direction = direction%2;
	}
	else if(monsterType == 1){
		direction = direction%2+2;
	}
	else if(monsterType == 2){

	
	}



	if(direction == 0){
		//Left
		nextPosition = vec3(currentPosition.x-2, currentPosition.y+2, currentPosition.z);
		if(checkOut(cubeList, nextPosition, currentCubeTotal)==true){
			setRotate(-90);
			resultPosition = vec3(currentPosition.x-2, currentPosition.y+2, currentPosition.z);
			//setTranlation(currentPosition.x-2, currentPosition.y+2, currentPosition.z);

			//currentIndex = getIndex(cubeList, nextPosition, currentCubeTotal);
			return resultPosition;
		}

	}
	else if(direction ==1){
		//Right
		nextPosition = vec3(currentPosition.x+2, currentPosition.y-2, currentPosition.z);
		if(checkOut(cubeList, nextPosition, currentCubeTotal)==true){
			setRotate(90);
			resultPosition = vec3(currentPosition.x+2, currentPosition.y-2, currentPosition.z);
			//setTranlation(currentPosition.x+2, currentPosition.y-2, currentPosition.z);
			//currentIndex = getIndex(cubeList, nextPosition, currentCubeTotal);
			return resultPosition;
		}
	}
	else if(direction ==2){
		//Up
		
		nextPosition = vec3(currentPosition.x, currentPosition.y+2, currentPosition.z-2);
		if(checkOut(cubeList, nextPosition, currentCubeTotal)==true){
			setRotate(180);
			resultPosition = vec3(currentPosition.x, currentPosition.y+2, currentPosition.z-2);
			//setTranlation(currentPosition.x, currentPosition.y+2, currentPosition.z-2);
			//setRotate(180);
			//currentIndex = getIndex(cubeList, nextPosition, currentCubeTotal);
			return resultPosition;
		}
	}
	else if(direction ==3){
		//Down
		nextPosition = vec3(currentPosition.x, currentPosition.y-2, currentPosition.z+2);
		if(checkOut(cubeList, nextPosition, currentCubeTotal)==true){
			setRotate(0);
			resultPosition = vec3(currentPosition.x, currentPosition.y-2, currentPosition.z+2);
			//setTranlation(currentPosition.x, currentPosition.y-2, currentPosition.z+2);

			//currentIndex = getIndex(cubeList, nextPosition, currentCubeTotal);
			return resultPosition;
		}
	}
	
	return vec3(10,10,10);

}
bool QBert_Cube_Monster::checkOut(vector<QBert_Cube> cubeList, vec3 position, int currentCubeTotal){
	//in true, out false
	int i =4;
	while (i < currentCubeTotal){
		//cout <<"checking cube " << input.cubeList[i].index << endl;
		if(position.x == cubeList[i].centerPosition.x && position.z == cubeList[i].centerPosition.z && position.y - cubeList[i].centerPosition.y < 2){
			//cout<< "On cube " << i<< endl;
			return true;
		}
		else{
			i++;
		}
	}	
	
	return false;
}
int QBert_Cube_Monster::updateCurrentPosition(){

}
int QBert_Cube_Monster::getIndex(vector<QBert_Cube> cubeList, vec3 position, int currentCubeTotal){
	//in true, out false
	int i =0;
	while (i < currentCubeTotal){
		//cout <<"checking cube " << input.cubeList[i].index << endl;
		if(position.x == cubeList[i].centerPosition.x && position.z == cubeList[i].centerPosition.z && position.y - cubeList[i].centerPosition.y < 2){
			//cout<< "On cube " << i<< endl;
			return i;
		}
		else{
			i++;
		}
	}	
	
	return -1;
}
void QBert_Cube_Monster::setBaseNumber(int baseNumber){
	int textureIndex;
	for(int i =0; i<6;i++){

		if(i==2){
			textureIndex = baseNumber;
		}
		else{
			textureIndex = 0;
		}
		uvArray[i*18+0] = 0.0f;
		uvArray[i*18+1] = 1.0f;
		uvArray[i*18+2] = textureIndex; 

		uvArray[i*18+3] = 1.0f;
		uvArray[i*18+4] = 1.0f;
		uvArray[i*18+5] = textureIndex; 

		uvArray[i*18+6] = 1.0f;
		uvArray[i*18+7] = 0.0f;
		uvArray[i*18+8] = textureIndex; 

		uvArray[i*18+9] = 0.0f;
		uvArray[i*18+10] = 1.0f;
		uvArray[i*18+11] = textureIndex; 

		uvArray[i*18+12] = 1.0f;
		uvArray[i*18+13] = 0.0f;
		uvArray[i*18+14] = textureIndex; 

		uvArray[i*18+15] = 0.0f;
		uvArray[i*18+16] = 0.0f;
		uvArray[i*18+17] = textureIndex; 
	}
}