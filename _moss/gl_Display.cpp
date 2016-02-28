#include "gl_Display.h"


bool gl_Display::Init(GLFWwindow* &Window, int ScreenWidth, int ScreenHeight, string WindowTitle){
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	// Open a window and create its OpenGL context 
	Window = glfwCreateWindow( ScreenWidth, ScreenHeight, WindowTitle.c_str(), NULL, NULL); 
	if( Window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(Window); 
	
	// Initialize GLEW 
	glewExperimental=true; 
	// Needed in core profile 
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	return true;

}
bool gl_Display::InitInfo( ShaderInfo &Info, int NumberOfTriangle, int VertexPerTriangle,  InputData input,  vector<int> triangleNumberCount, int numberOfMonster,  GameStatus &gameStatus){
	glGenVertexArrays( 1, &Info.vertexArray );
	glBindVertexArray( Info.vertexArray );

	int floatPerVertex = 3;

	//vertex
	GLfloat* vertex_buffer_data;

	//vertex_buffer_data = new GLfloat[NumberOfTriangle*VertexPerTriangle*3+36*(HierachyTree.size()-1)];
	vertex_buffer_data = new GLfloat[NumberOfTriangle*VertexPerTriangle*floatPerVertex];

	GLfloat* color_buffer_data;

	color_buffer_data = new GLfloat[NumberOfTriangle*VertexPerTriangle*floatPerVertex];
	vec4 transformedVertex;
	vec4 tempVertex;

	GLfloat* uv_buffer_data;

	uv_buffer_data = new GLfloat[NumberOfTriangle*VertexPerTriangle*floatPerVertex];

	GLfloat* constant_buffer_data;

	constant_buffer_data = new GLfloat[NumberOfTriangle*VertexPerTriangle*floatPerVertex];


	int currentTriangleCount;
	//fill in cube data
	int numberOfCube = input.cubeList.size();
	//cout << "Have " << triangleNumberCount.size() << " cubes" << endl;
	currentTriangleCount = 0;

	//Cube
	for(int i =0; i < numberOfCube ; i++){
		for(int j =0; j< 12; j++){

			for(int k =0; k<3; k++){
				//cout <<  j*VertexPerTriangle*floatPerVertex+k
				//<<", "<< j*VertexPerTriangle*floatPerVertex <<endl;
				
				tempVertex = vec4(input.cubeList[i].vertexArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0], input.cubeList[i].vertexArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1], input.cubeList[i].vertexArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
				transformedVertex = input.cubeList[i].translation * tempVertex;

				//vertex_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = cubeList[i].vertexArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
				//vertex_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = cubeList[i].vertexArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
				//vertex_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = cubeList[i].vertexArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

				vertex_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
				vertex_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
				vertex_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;

				//color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.cubeList[i].colorArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
				//color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.cubeList[i].colorArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
				//color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.cubeList[i].colorArray[j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
				if(j == 0 || j ==1){
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.cubeList[i].colorBottom.r;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.cubeList[i].colorBottom.g;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.cubeList[i].colorBottom.b;

				}
				else if(j == 2 || j ==3){
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.cubeList[i].colorTop.r;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.cubeList[i].colorTop.g;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.cubeList[i].colorTop.b;
				}
				else if(j == 4 || j ==5){
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.cubeList[i].colorFront.r;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.cubeList[i].colorFront.g;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.cubeList[i].colorFront.b;
				}
				else if(j == 6 || j ==7){
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.cubeList[i].colorBack.r;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.cubeList[i].colorBack.g;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.cubeList[i].colorBack.b;
				}
				else if(j == 8 || j ==9){
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.cubeList[i].colorLeft.r;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.cubeList[i].colorLeft.g;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.cubeList[i].colorLeft.b;
				}
				else if(j == 10 || j ==11){
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.cubeList[i].colorRight.r;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.cubeList[i].colorRight.g;
					color_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.cubeList[i].colorRight.b;
				}
				uv_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 0;
				uv_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = 0;
				uv_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = 0;

				constant_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 0;
				constant_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = 0;
				constant_buffer_data[i*12*VertexPerTriangle*floatPerVertex+j*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = 0;
			}
			currentTriangleCount++;
		}
		//cout << "***" <<i << endl;
		//cout << "****cube "<<i <<" color (" <<input.cubeList[i].colorTop.r
		//				                  <<", "<<input.cubeList[i].colorTop.g
		//				                  <<", "<<input.cubeList[i].colorTop.b << ")" << endl;
	}

	//QBert
	for(int i = 0; i< triangleNumberCount[1]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			
			tempVertex = vec4( input.QBert.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.QBert.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.QBert.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			transformedVertex =  input.QBert.translation * input.QBert.rotateMatrix * input.QBert.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.QBert.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.QBert.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.QBert.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.QBert.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.QBert.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.QBert.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = 0;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.QBert.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.QBert.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.QBert.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.QBert.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];



		}
		currentTriangleCount++;
	}

	//Monster
	for(int j =0; j < numberOfMonster; j++){
		for(int i = 0; i< triangleNumberCount[2+j]; i++){
			for(int k =0; k<3; k++){
				//cout <<  j*VertexPerTriangle*floatPerVertex+k
				//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			
				tempVertex = vec4( input.monsterList[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.monsterList[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.monsterList[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
				transformedVertex =  input.monsterList[j].translation * input.monsterList[j].rotateMatrix * input.monsterList[j].scaleMatrix * tempVertex;

				vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
				vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
				vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
				//color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.monsterList[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
				//color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.monsterList[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
				//color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.monsterList[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
				
				if(i == 0 || i ==1){
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.monsterList[j].colorBottom.r;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.monsterList[j].colorBottom.g;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.monsterList[j].colorBottom.b;

				}
				else if(i == 2 || i ==3){
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.monsterList[j].colorTop.r;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.monsterList[j].colorTop.g;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.monsterList[j].colorTop.b;
				}
				else if(i == 4 || i ==5){
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.monsterList[j].colorFront.r;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.monsterList[j].colorFront.g;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.monsterList[j].colorFront.b;
				}
				else if(i == 6 || i ==7){
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.monsterList[j].colorBack.r;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.monsterList[j].colorBack.g;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.monsterList[j].colorBack.b;
				}
				else if(i == 8 || i ==9){
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.monsterList[j].colorLeft.r;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.monsterList[j].colorLeft.g;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.monsterList[j].colorLeft.b;
				}
				else if(i == 10 || i ==11){
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.monsterList[j].colorRight.r;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.monsterList[j].colorRight.g;
					color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.monsterList[j].colorRight.b;
				}
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.monsterList[j].uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.monsterList[j].uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
				//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.monsterList[j].uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
				if(i==4 ||i==5){
					uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.monsterList[j].textureBaseNumber;
				}
				else{
					uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
				
				}
				constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =0;
				constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =0;
				constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;

			}
			currentTriangleCount++;
		}
	}
	//Screen ground
	mat4 x_rotate = rotate(mat4(), glm::radians(45.0f), glm::vec3(0,1,0));
	for(int i = 0; i< triangleNumberCount[2+numberOfMonster]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.screenGround.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.screenGround.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.screenGround.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =   input.screenGround.rotateMatrix * input.screenGround.translation * x_rotate * input.screenGround.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.screenGround.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.screenGround.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.screenGround.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =35+gameStatus.gameLevel;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.screenGround.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.screenGround.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];



		}
		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+0] =0;
		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+1] =1;
		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+2] =1;

		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+3] =1;
		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+4] =1;
		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+5] =1;
		
		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+6] =1;
		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+7] =0;
		//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+8] =1;

		currentTriangleCount++;
	}


	//cry
	//mat4 x_rotate = rotate(mat4(), glm::radians(45.0f), glm::vec3(0,1,0));
	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+1]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.cry.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.cry.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.cry.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =   input.cry.rotateMatrix * input.cry.translation * input.cry.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.cry.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.cry.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.cry.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.cry.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.cry.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =10;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.cry.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 0;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.cry.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.cry.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//spin disk

	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+2]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.spin1.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.spin1.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.spin1.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =   input.spin1.translation *input.spin1.rotateMatrix * input.spin1.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.spin1.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.spin1.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.spin1.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin1.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.spin1.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==2 ||i==3){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =11+gameStatus.gameLevel;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin1.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 0;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.spin1.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.spin1.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}


	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+3]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.spin2.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.spin2.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.spin2.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.spin2.translation * input.spin2.rotateMatrix * input.spin2.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.spin2.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.spin2.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.spin2.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.spin2.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==2 ||i==3){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =11+gameStatus.gameLevel;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 0;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//Score board
for(int j=0;j<5;j++){
	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+4]/5; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.scoreboard[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.scoreboard[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.scoreboard[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.scoreboard[j].translation * input.scoreboard[j].rotateMatrix * input.scoreboard[j].scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.scoreboard[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.scoreboard[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.scoreboard[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.scoreboard[j].uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.scoreboard[j].uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =14+gameStatus.digits[j];
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.scoreboard[j].constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.scoreboard[j].constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}
}

// live number
	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+5]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.liveNumber.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.liveNumber.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.liveNumber.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.liveNumber.translation * input.liveNumber.rotateMatrix * input.liveNumber.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.liveNumber.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.liveNumber.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.liveNumber.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.liveNumber.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.liveNumber.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =24+gameStatus.lives;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.liveNumber.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.liveNumber.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//QBert lives
for(int j=0;j<10;j++){
	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+6]/10; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.QBertLives[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.QBertLives[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.QBertLives[j].vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.QBertLives[j].translation * input.QBertLives[j].rotateMatrix * input.QBertLives[j].scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.QBertLives[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.QBertLives[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.QBertLives[j].colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.QBertLives[j].uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.QBertLives[j].uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			
			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =2;

			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			}
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.QBertLives[j].constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.QBertLives[j].constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}
}

//opening Back;
	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+7]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.opoeningBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.opoeningBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.opoeningBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.opoeningBack.translation * input.opoeningBack.rotateMatrix * input.opoeningBack.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.opoeningBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.opoeningBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.opoeningBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.opoeningBack.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.opoeningBack.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =38;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.opoeningBack.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.opoeningBack.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//opening start

	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+8]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.openingStart.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.openingStart.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.openingStart.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.openingStart.translation * input.openingStart.rotateMatrix * input.openingStart.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.openingStart.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.openingStart.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.openingStart.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.openingStart.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.openingStart.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =39;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.openingStart.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.openingStart.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//opening End

	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+9]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.openingExit.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.openingExit.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.openingExit.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.openingExit.translation * input.openingExit.rotateMatrix * input.openingExit.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.openingExit.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.openingExit.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.openingExit.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.openingExit.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.openingExit.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =40;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.openingExit.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.openingExit.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//opening button

	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+10]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.openingButton.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.openingButton.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.openingButton.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.openingButton.translation * input.openingButton.rotateMatrix * input.openingButton.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.openingButton.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.openingButton.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.openingButton.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.openingButton.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.openingButton.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.openingButton.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.openingButton.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}


//trans Level
//opening Back;
	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+11]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.transBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.transBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.transBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.transBack.translation * input.transBack.rotateMatrix * input.transBack.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.transBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.transBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.transBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.transBack.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.transBack.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.transBack.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.transBack.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//opening start

	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+12]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.openingStart.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.openingStart.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.openingStart.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.openingStart.translation * input.openingStart.rotateMatrix * input.openingStart.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.openingStart.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.openingStart.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.openingStart.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.openingStart.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.openingStart.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				if(gameStatus.gameRoom == 2){
					uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =41;
				}
				else{
					uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =42;
				
				}
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.openingStart.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.openingStart.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//trans monster




	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+13]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.transMon1.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.transMon1.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.transMon1.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.transMon1.translation * input.transMon1.rotateMatrix * input.transMon1.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.transMon1.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.transMon1.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.transMon1.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.transMon1.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.transMon1.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =6;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 0;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.transMon1.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.transMon1.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+13]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.transMon2.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.transMon2.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.transMon2.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.transMon2.translation * input.transMon2.rotateMatrix * input.transMon2.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.transMon2.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.transMon2.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.transMon2.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.transMon2.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.transMon2.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =7;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 0;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.transMon2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.transMon2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+13]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.transMon3.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.transMon3.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.transMon3.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.transMon3.translation * input.transMon3.rotateMatrix * input.transMon3.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.transMon3.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.transMon3.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.transMon3.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.transMon3.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.transMon3.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =8;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 0;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.transMon3.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.transMon3.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}



	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+11]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.endingBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.endingBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.endingBack.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.endingBack.translation * input.endingBack.rotateMatrix * input.endingBack.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.endingBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.endingBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.endingBack.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.endingBack.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.endingBack.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.endingBack.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.endingBack.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}

//opening start

	for(int i = 0; i< triangleNumberCount[2+numberOfMonster+12]; i++){
		for(int k =0; k<3; k++){
			//cout <<  j*VertexPerTriangle*floatPerVertex+k
			//<<", "<< j*VertexPerTriangle*floatPerVert+ex <<endl;
			tempVertex = vec4( input.endingSign.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0],  input.endingSign.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1],  input.endingSign.vertexArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2], 1.0f);
			
			transformedVertex =    input.endingSign.translation * input.endingSign.rotateMatrix * input.endingSign.scaleMatrix * tempVertex;

			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = transformedVertex.x;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = transformedVertex.y;
			vertex_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = transformedVertex.z;
			
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = input.endingSign.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] = input.endingSign.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			color_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] = input.endingSign.colorArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
		
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.endingSign.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.endingSign.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =1;

			if(i==4 ||i==5){
				if(gameStatus.gameRoom == 2){
					uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =43;
				}
				else{
					uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =43;
				
				}
			}
			else{
				uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =0;
			
			}
			//constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] =input.spin2.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+0] = 1;

			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1] =input.endingSign.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+1];
			//uv_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.screenGround.uvArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];
			constant_buffer_data[(currentTriangleCount)*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2] =input.endingSign.constantArray[i*VertexPerTriangle*floatPerVertex+k*floatPerVertex+2];

		}
		currentTriangleCount++;
	}



/*
	GLfloat tempVertexArray[] = 
	{ 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 0.0f, -1.0f, 0.0f,

	};
	memcpy( vertex_buffer_data, tempVertexArray, sizeof( tempVertexArray ) );
*/
	QBert_Cube cube;

	glGenBuffers( 1, &Info.vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, Info.vertexBuffer );
	//this line sent data to GPU

	//glBufferData( GL_ARRAY_BUFFER, (NumberOfTriangle*VertexPerTriangle*floatPerVertex)*sizeof(float), vertex_buffer_data, GL_STATIC_DRAW );
	glBufferData( GL_ARRAY_BUFFER, (NumberOfTriangle*VertexPerTriangle*floatPerVertex)*sizeof(float), vertex_buffer_data, GL_STATIC_DRAW );

	glGenBuffers( 1, &Info.colorBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, Info.colorBuffer );
	//this line sent data to GPU

	//glBufferData( GL_ARRAY_BUFFER, (NumberOfTriangle*VertexPerTriangle*floatPerVertex)*sizeof(float), vertex_buffer_data, GL_STATIC_DRAW );
	glBufferData( GL_ARRAY_BUFFER, (NumberOfTriangle*VertexPerTriangle*floatPerVertex)*sizeof(float), color_buffer_data, GL_STATIC_DRAW );

	glGenBuffers( 1, &Info.uvBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, Info.uvBuffer );
	//this line sent data to GPU

	//glBufferData( GL_ARRAY_BUFFER, (NumberOfTriangle*VertexPerTriangle*floatPerVertex)*sizeof(float), vertex_buffer_data, GL_STATIC_DRAW );
	glBufferData( GL_ARRAY_BUFFER, (NumberOfTriangle*VertexPerTriangle*floatPerVertex)*sizeof(float), uv_buffer_data, GL_STATIC_DRAW );

	glGenBuffers( 1, &Info.constantBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, Info.constantBuffer );
	//this line sent data to GPU

	//glBufferData( GL_ARRAY_BUFFER, (NumberOfTriangle*VertexPerTriangle*floatPerVertex)*sizeof(float), vertex_buffer_data, GL_STATIC_DRAW );
	glBufferData( GL_ARRAY_BUFFER, (NumberOfTriangle*VertexPerTriangle*floatPerVertex)*sizeof(float), constant_buffer_data, GL_STATIC_DRAW );
	//
/*
	GLfloat tempUVArray[] = { 
		0.000059f, 1.0f-0.000004f,
		0.000103f, 1.0f-0.336048f,
 		0.335973f, 1.0f-0.335903f,
 		1.000023f, 1.0f-0.000013f,
		0.667979f, 1.0f-0.335851f,
 		0.999958f, 1.0f-0.336064f,
	};	
	memcpy( uv_buffer_data, tempUVArray, sizeof( tempUVArray ) );


	GLfloat tempTextureArray[] = { 
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		1.0f,
	};	
	memcpy( texture_buffer_data, tempTextureArray, sizeof( tempTextureArray ) );

	GLfloat tempTransformArray[] = { 
		1.0f,
		1.0f,
		1.0f,
		2.0f,
		2.0f,
		2.0f,
	};
	memcpy( transform_buffer_data, tempTransformArray, sizeof( tempTransformArray ) );
*/

	return true;
}
GLuint gl_Display::InitShader( const char* vertex_file_path, const char* fragment_file_path ){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader( GL_VERTEX_SHADER );
	GLuint FragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}



	GLint Result = GL_FALSE;
	int InfoLogLength;



	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);


	//Error handling: TODO

	return ProgramID;

}

bool gl_Display::End(GLFWwindow* &Window){
	glfwDestroyWindow(Window);
    glfwTerminate();

	//Error handling: TODO

	return true;
}
void gl_Display::deleteLastLevel(ShaderInfo &Info){
	

}
