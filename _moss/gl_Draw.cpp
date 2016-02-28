#include "gl_Draw.h"


bool gl_Draw::Draw(GLFWwindow* &Window, ShaderInfo &Info, GLuint NumberOfTriangles, const uint NumberOfVertex, const uint NumberOfFloat){
	// Draw
	// clear the screen
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	// Swap buffers
	glfwSwapBuffers(Window);
	glfwPollEvents();	
	
	//Error handling: TODO
	return true;
}
void gl_Draw::SendDataToShader(ShaderInfo &Info, GLuint NumberOfTriangles, const uint NumberOfVertex, const uint NumberOfFloat, int Stage, vector<int> TriangleCount,  int currentCubeTotal, int numberOfMonster, int screenChange, GameStatus &gameStatus){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	 
	// Use our shader
	glUseProgram( Info.programId );

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, Info.vertexBuffer );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0	);

	glEnableVertexAttribArray( 1 );
	glBindBuffer( GL_ARRAY_BUFFER, Info.colorBuffer );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0	);

	glEnableVertexAttribArray( 2 );
	glBindBuffer( GL_ARRAY_BUFFER, Info.uvBuffer );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0	);
	
	glEnableVertexAttribArray( 3 );
	glBindBuffer( GL_ARRAY_BUFFER, Info.constantBuffer );
	glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 0, ( void* ) 0	);

	int platformTriangle;
	int currentTriangleCount = 0;

	//cout <<"***" <<currentCubeTotal << endl;

	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){
		glDrawArrays(GL_TRIANGLES, 0, currentCubeTotal*12*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount + TriangleCount[0];

	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){
		glDrawArrays(GL_TRIANGLES, TriangleCount[0]*NumberOfVertex, TriangleCount[1]*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[1];

	for(int i =0; i < numberOfMonster; i++){
		if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){

			glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, TriangleCount[2+i]*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
		}
		currentTriangleCount = currentTriangleCount +TriangleCount[2+i];
	}
	//if(screenChange ==0){
	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){

		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, TriangleCount[2+numberOfMonster]*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	//}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster];

	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){
		if(gameStatus.printCry >0){
			glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, TriangleCount[2+numberOfMonster+1]*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
		}
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+1];
	//spin disks
	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, TriangleCount[2+numberOfMonster+2]*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+2];

	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, TriangleCount[2+numberOfMonster+3]*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+3];

	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, TriangleCount[2+numberOfMonster+4]*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+4];
	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, TriangleCount[2+numberOfMonster+5]*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+5];
	if(gameStatus.gameRoom == 1 ||gameStatus.gameRoom == 3 || gameStatus.gameRoom == 5){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+6])/10*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+6];

	if(gameStatus.gameRoom == 0){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+7])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+7];
	if(gameStatus.gameRoom == 0){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+8])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+8];
	if(gameStatus.gameRoom == 0){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+9])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+9];
	if(gameStatus.gameRoom == 0){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+10])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+10];

	
	if(gameStatus.gameRoom == 2 ||gameStatus.gameRoom == 4){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+11])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+11];

	if(gameStatus.gameRoom == 2 ||gameStatus.gameRoom == 4){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+12])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+12];
	
	if(gameStatus.gameRoom == 2 ||gameStatus.gameRoom == 4){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+13])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+13];	

	if(gameStatus.gameRoom == 2 ||gameStatus.gameRoom == 4){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+14])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+14];	

	if(gameStatus.gameRoom == 2 ||gameStatus.gameRoom == 4){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+15])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+15];	


	if(gameStatus.printEnd == 1){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+16])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+16];	

	if(gameStatus.printEnd == 1){
		glDrawArrays(GL_TRIANGLES, currentTriangleCount*NumberOfVertex, (TriangleCount[2+numberOfMonster+17])*gameStatus.lives*NumberOfVertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
	}
	currentTriangleCount = currentTriangleCount +TriangleCount[2+numberOfMonster+17];	

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);


}
void gl_Draw::SetMVP(ShaderInfo &Info, GLuint const ScreenWidth, GLuint const ScreenHeight, GLuint const ScreenScale, vec3 eyePosition, mat4 const platformTranslation){
	//mat4 projection = glm::ortho((-1.0f)*ScreenWidth/2/ScreenScale,(1.0f)*ScreenWidth/2/ScreenScale, (-1.0f)*ScreenHeight/2/ScreenScale, (1.0f)*ScreenHeight/2/ScreenScale, +1.0f, -50.0f);
	
	//mat4 ortho = glm::mat4(1.0f);

	mat4 ortho = glm::ortho((-1.0f)*ScreenWidth/2/ScreenScale,(1.0f)*ScreenWidth/2/ScreenScale, (-1.0f)*ScreenHeight/2/ScreenScale, (1.0f)*ScreenHeight/2/ScreenScale, -100.0f, 500.0f);

	mat4 projection = glm::mat4(1.0f);

	//mat4 projection = perspective(radians(40.0f), (float)ScreenWidth/ScreenHeight, 1.0f, 10.0f);

	mat4 camera = glm::lookAt(
					 glm::vec3(eyePosition.x, eyePosition.y, eyePosition.z),
                     glm::vec3(0.0f, 0.0f, 0.0f),
                     glm::vec3(0.0f, 1.0f, 0.0f)
                     );
	//glm::mat4 camera = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));

	mat4 model = glm::mat4(1.0f);
	//mat4 model = glm::rotate(glm::mat4(), glm::radians(-45.0f), glm::vec3(0,1,0));
	//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1,0,0));
	//model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0,0,1));

	mat4 MVP = ortho * projection * camera * platformTranslation * model;

	GLint MVPUniformLocation = glGetUniformLocation( Info.programId, "MVP");
	glUniformMatrix4fv( MVPUniformLocation, 1, GL_FALSE, &MVP[0][0]);
}
void gl_Draw::SendTriangleToShader(ShaderInfo &Info, GLuint NumberOfTriangles, const uint NumberOfVertex, const uint NumberOfFloat){
	
	int floatPerVertex = 3;
	GLfloat tempVertexArray[9];
	GLfloat tempColorArray[9];
	QBert_Cube cube;

	for(int i = 0; i < NumberOfTriangles; i++){
		for(int j = 0; j< 3; j++){
			tempVertexArray[j*3+0] = cube.vertexArray[i*9+j*3+0];
			tempVertexArray[j*3+1] = cube.vertexArray[i*9+j*3+1];
			tempVertexArray[j*3+2] = cube.vertexArray[i*9+j*3+2];

			tempColorArray[j*3+0] = cube.colorArray[i*9+j*3+0];
			tempColorArray[j*3+1] = cube.colorArray[i*9+j*3+1];
			tempColorArray[j*3+2] = cube.colorArray[i*9+j*3+2];
			//cout <<  i*9+j*3+0 << endl;
			//cout << "This point is (" << cube.vertexArray[i*9+j*3+0]
		    //                    <<", "<< cube.vertexArray[i*9+j*3+1]
			//                    <<", "<< cube.vertexArray[i*9+j*3+2] << ")" << endl;

		}
		//cout <<  i*NumberOfVertex*floatPerVertex << endl;
		glBufferSubData(GL_ARRAY_BUFFER, i*NumberOfVertex*floatPerVertex*sizeof(float), NumberOfVertex*floatPerVertex*sizeof(float),tempVertexArray);
		//glBufferSubData(GL_ARRAY_BUFFER, i*NumberOfVertex*floatPerVertex*sizeof(float), NumberOfVertex*floatPerVertex*sizeof(float),tempColorArray);
	
	}
}