/*===============
License information:

Project name: QBert Game

Author: Yi-Chun Chen (RimiChen)
student ID: 200110436
Unity ID: ychen74

References:

1. Tutorials for modern OpenGL (3.3+)
link: http://www.opengl-tutorial.org/

2. 3D Computer Graphics Using OpenGL
link: https://www.youtube.com/playlist?list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY

=================*/

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

/*=================
self-defined library
===================*/
#include "self_defined.h"


/*===============
global variables
and magic numbers
convention: 
- global: Pascal casing.
- local: Camel casing
- function input: Pascal casing
- function output: Pascal casing
- function name: Pascal casing
=================*/


/*=============
Define constant
==============*/
const uint NUMBER_OF_VERTEX_PER_TRI = 3;
// vertex 3, color 3
const uint NUMBER_OF_FLOAT_PER_VERTEX = 6;
const uint TRIANGLE_BYTE_SIZE = NUMBER_OF_VERTEX_PER_TRI * NUMBER_OF_FLOAT_PER_VERTEX * sizeof(float);


/*===============
Globala Varialbes
================*/
GLFWwindow* Window;
GLuint ScreenWidth;
GLuint ScreenHeight;
string WindowTitle;
string VertexShader;
string FragmentShader;
ShaderInfo Info;
GLuint ScreenScale;
GLuint Stage;
vec3 eyePosition;


InputData input;
QBert_Cube_QBert QBert;
vector<QBert_Cube> cubeList;
vector<QBert_Cube_Monster> monsterList;
vector<int> monsterUsedList;
vector<QBert_Cube_Item> itemList;
GameStatus gameStatus;
vector<QBert_Cube_Item> spinList;



vector<int> checkCubeState;
int currentCubeTotal;
int needToAchieve;

int ReloadData;
float Bound_x;
float Bound_y;
float Bound_z;

int animation;
int dead;
int win;
int jump;

int ScreenChange;

LARGE_INTEGER startTime,endTime,fre;
float timeDiff;
vector<int> numberOfMonsterTriangles;
vector<int> triangleCountVector;

vec3 nextPosition;
vec3 lastPosition;
vec3* monsterNextPosition;
vec3* monsterLastPosition;

float spin1Rotate;
float spin2Rptate;

int score;
int lives;

int goToNext;
int gameRoom;


LARGE_INTEGER endStartTime;
LARGE_INTEGER endEndTime;
bool endFlag;


/*======
Methods
=======*/
void KeyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
int GeneratePlatform(vector<QBert_Cube> &cubeList,  int const numberOfPlatformLayer);
int GenerateMonter(vector<QBert_Cube_Monster> &monsterList, int numberOfMonster);
int GenerateItem(vector<QBert_Cube_Monster> &itemList);

bool timeDelay(double delay);
bool flexibleTimeDelay(double delay, LARGE_INTEGER &inputStartTime, LARGE_INTEGER &inputEndTime);
int checkPosition(vector<QBert_Cube> &cubeList, vec3 objectPosition);
void checkWin();
/*=============
Program Entress
==============*/
int main(int argc, char** argv){


	// initailize variables
	WindowTitle = "QBert game";
	ScreenWidth = 1024;
	ScreenHeight = 768;
	ScreenScale = 30;
	int numberOfTriangles;
	int numberOfCubes;
	int numberOfPlatformLayer;
	int currentLevel;
	mat4 platformTranslation;

	//deal with triangle counts
	int numberOfCubeTriangles;
	int numberOfQBertTriangles;
	int numberOfMonster;
	int numberOfItem;

	endFlag = false;
	
	LARGE_INTEGER monsterStartTime;
	LARGE_INTEGER monsterEndTime;


	LARGE_INTEGER jumpStartTime;
	LARGE_INTEGER jumpEndTime;

	srand (time(NULL));
	

	
	VertexShader = "_moss/vs.glsl";
	FragmentShader = "_moss/fs.glsl";

	//initialize shader info
	Info.programId = NULL;
	Info.vertexArray = NULL;
	Info.vertexBuffer = NULL;
	Info.colorArray = NULL;
	Info.colorBuffer = NULL;
	Info.uvArray = NULL;
	Info.uvBuffer = NULL;
	Info.constantArray = NULL;
	Info.constantBuffer = NULL;

	cout << " System: Welcome to QBert Game."<< endl;

	//Self defined class declarition
	gl_Display display;
	gl_Draw draw;

	// initalize openGL
	display.Init( Window, ScreenWidth, ScreenHeight, WindowTitle);
	Info.programId = display.InitShader( VertexShader.c_str(), FragmentShader.c_str() );


	// set Key callback
	glfwSetKeyCallback( Window, KeyCallback);

	//Game setting
	numberOfPlatformLayer = 9;
	numberOfMonster = 4;
	numberOfItem = 0;
	

	currentLevel = numberOfPlatformLayer;
	//numberOfCubes = 3;
	//numberOfTriangles = numberOfCubes * 12;
	
	Stage = 5;

	currentCubeTotal = 0;
	needToAchieve =0;
	for(int i =1; i <=Stage+1; i++){
		for(int j =1; j <= i; j++){
			currentCubeTotal = currentCubeTotal +j;
		}
		needToAchieve = needToAchieve +i;
	}

	cout << "currentTotal " << currentCubeTotal << " need to achieve " << needToAchieve <<endl;	

	//generate cube list (the platform)



	triangleCountVector.empty();

	numberOfCubeTriangles = GeneratePlatform(cubeList, numberOfPlatformLayer);
	triangleCountVector.push_back(numberOfCubeTriangles);



	//Load QBert
	//first using cube as QBert
	numberOfQBertTriangles = QBert.numberOfTriangle;
	QBert.setAllColor(vec3(255.0/255.0,148.0/255.0, 43.0/255.0));
	QBert.setScale(0.5, 0.5 ,0.5);
	QBert.setTranlation(0, 1.5, 0);
	triangleCountVector.push_back(numberOfQBertTriangles);

	//Load Monsters
	GenerateMonter(monsterList, numberOfMonster);

	//Add small things;
	QBert_Cube_Item ScreenGround;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	ScreenGround.setColor_Front(vec3(1.0, 1.0, 0.5));
	ScreenGround.setTranlation(0, 0, 0);
	ScreenGround.setScale( 1, 1 ,-0.1);
	ScreenGround.setRotate(135);

	triangleCountVector.push_back(ScreenGround.numberOfTriangle);

	//Cry
	QBert_Cube_Item cry;
	cry.setAllColor(vec3(1.0,1.0,1.0));
	cry.setTranlation(10, 5, 0);
	cry.setScale( 2, 1 ,0.1);

	triangleCountVector.push_back(cry.numberOfTriangle);

	//Spin disks
	QBert_Cube_Item spin1;
	spin1.setAllColor(vec3(0.0,0.0,0.0));
	spin1.setTranlation(cubeList[19].centerPosition.x , cubeList[19].centerPosition.y+2, cubeList[19].centerPosition.z-2);
	spin1.setRotate(45);
	spin1.setScale( 1 , 0.2 ,1);
	triangleCountVector.push_back(spin1.numberOfTriangle);
	spinList.push_back(spin1);

	QBert_Cube_Item spin2;
	spin2.setAllColor(vec3(0.0,0.0, 0.0));
	spin2.setTranlation(cubeList[10].centerPosition.x-2 , cubeList[10].centerPosition.y+2, cubeList[10].centerPosition.z);
	spin2.setRotate(45);
	spin2.setScale( 1 , 0.2 ,1);
	triangleCountVector.push_back(spin2.numberOfTriangle);
	spinList.push_back(spin2);

	QBert_Cube_Item* scoreBoard;
	scoreBoard = new QBert_Cube_Item[5];
	for(int i =0; i< 5; i++){
		scoreBoard[i].setAllColor(vec3(1.0,1.0,1.0));

		scoreBoard[i].setTranlation(-0.9, 0.9-i*0.1, 0);
		scoreBoard[i].setScale(0.05,0.05,0.2);
		scoreBoard[i].setRotate(180);
	}
	triangleCountVector.push_back(5*scoreBoard[0].numberOfTriangle);

	//lives
	QBert_Cube_Item liveNumber;
	//QBert_Cube_QBert lives[9];
	liveNumber.setAllColor(vec3(1.0,1.0,1.0));
	liveNumber.setTranlation(-0.9, -0.8, 0.0);
	liveNumber.setScale(0.05,0.05,0.2);
	liveNumber.setRotate(180);
	triangleCountVector.push_back(liveNumber.numberOfTriangle);

	QBert_Cube_QBert* QBertlives;
	QBert_Cube_QBert tempQBertForLive;
	QBertlives = new QBert_Cube_QBert[10];
	for(int i =0; i < 10; i++){
		QBertlives[i] = tempQBertForLive;
		QBertlives[i].setAllColor(vec3(255.0/255.0,148.0/255.0, 43.0/255.0));
		QBertlives[i].setScale(0.03, 0.03 ,0.05);
		QBertlives[i].setTranlation(-0.7+i*0.1,-0.8,-0.1);	
		QBertlives[i].setRotate(180);
	
	}
	triangleCountVector.push_back(10*12);


//Process animation

	//Add small things;
	QBert_Cube_Item openingBack;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	openingBack.setColor_Front(vec3(1.0, 1.0, 0.5));
	openingBack.setTranlation(0, 0, 0);
	openingBack.setScale( 1, 1 ,0);
	openingBack.setRotate(180);

	triangleCountVector.push_back(openingBack.numberOfTriangle);

	QBert_Cube_Item openingStart;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	openingStart.setColor_Front(vec3(1.0, 1.0, 0.5));
	openingStart.setTranlation(0, 0.2, 0);
	openingStart.setScale( 0.2, 0.1 ,0.5);
	openingStart.setRotate(180);

	triangleCountVector.push_back(openingStart.numberOfTriangle);
	
	QBert_Cube_Item openingExit;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	openingExit.setColor_Front(vec3(1.0, 1.0, 0.5));
	openingExit.setTranlation(0, -0.2, 0);
	openingExit.setScale( 0.2, 0.1 ,0.3);
	openingExit.setRotate(180);

	triangleCountVector.push_back(openingExit.numberOfTriangle);

	QBert_Cube_Item openingButton;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	openingButton.setColor_Front(vec3(0.0, 1.0, 0.0));
	openingButton.setTranlation(-0.3, 0.2, 0);
	openingButton.setScale( 0.05, 0.05 ,0.3);
	openingButton.setRotate(180);

	triangleCountVector.push_back(openingButton.numberOfTriangle);

//Trans Level
	QBert_Cube_Item transBack;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	transBack.setColor_Front(vec3(0.0,0.0,0.0));
	transBack.setTranlation(0, 0, 0);
	transBack.setScale( 1, 1 ,0);
	transBack.setRotate(180);

	triangleCountVector.push_back(transBack.numberOfTriangle);

	QBert_Cube_Item transStart;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	transStart.setColor_Front(vec3(1.0, 1.0, 0.5));
	transStart.setTranlation(0, 0.2, 0);
	transStart.setScale( 0.2, 0.1 ,0.5);
	transStart.setRotate(180);
	triangleCountVector.push_back(transStart.numberOfTriangle);

	QBert_Cube_Monster transMon1;
	transMon1.setAllColor(vec3(175.0/255.0,255.0/255.0, 157.0/255.0));
	transMon1.setScale(1,1,1);
	transMon1.setTranlation(0.0, 3.0, 0.0);

	triangleCountVector.push_back(transMon1.numberOfTriangle);
	QBert_Cube_Monster transMon2;
	transMon2.setAllColor(vec3(142.0/255.0,238.0/255.0, 255.0/255.0));
	transMon2.setScale(1,1,1);
	transMon2.setTranlation(15.0, -20.0, 5.0);

	triangleCountVector.push_back(transMon1.numberOfTriangle);

	QBert_Cube_Monster transMon3;
	transMon3.setAllColor(vec3(246.0/255.0,223.0/255.0, 121.0/255.0));
	transMon3.setScale(1,1,1);
	transMon3.setTranlation(-15.0, -20.0, -5.0);

	triangleCountVector.push_back(transMon1.numberOfTriangle);


	QBert_Cube_Item endingBack;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	endingBack.setColor_Front(vec3(0.0,0.0,0.0));
	endingBack.setTranlation(0, 0, 0);
	endingBack.setScale( 1, 1 ,0);
	endingBack.setRotate(180);

	triangleCountVector.push_back(transBack.numberOfTriangle);

	QBert_Cube_Item endingSign;
	//ScreenGround.setAllColor(vec3(1,0.0,0.5));
	endingSign.setColor_Front(vec3(1.0, 1.0, 0.5));
	endingSign.setTranlation(0, 0.2, 0);
	endingSign.setScale( 0.2, 0.1 ,0.5);
	endingSign.setRotate(180);
	triangleCountVector.push_back(transStart.numberOfTriangle);




	input.cubeList = cubeList;
	input.checkCubeState = checkCubeState;
	input.QBert = QBert;
	input.monsterList = monsterList;
	input.screenGround = ScreenGround;
	input.cry = cry;
	input.spin1 = spin1;
	input.spin2 = spin2;
	input.scoreboard = scoreBoard;
	input.liveNumber = liveNumber;
	input.QBertLives =QBertlives;

	input.opoeningBack = openingBack;
	input.openingStart = openingStart;
	input.openingExit = openingExit;
	input.openingButton = openingButton;

	input.transBack =transBack;
	input.transSign = transStart;
	input.transMon1 = transMon1;
	input.transMon2 = transMon2;
	input.transMon3 = transMon3;

	input.endingBack = endingBack;
	input.endingSign = endingSign;



	gameStatus.printCry =0;
	gameStatus.gameLevel =0;
	gameStatus.score = 0;
	gameStatus.lives = 10;

	numberOfTriangles = 0;
	for(int i = 0; i < triangleCountVector.size(); i++){
		numberOfTriangles = numberOfTriangles + triangleCountVector[i];
	}

	vec3 newColor;

	display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);

	ReloadData = 0;
	animation = 0;
	dead = 0;
	win = 0;

	int random;

	Bound_x = (float)Stage*2.0f;
	Bound_y = (float)Stage*(-2.0f);
	Bound_z = (float)Stage*2.0f;

	//cout << Bound_x << ", "<<Bound_y <<", " << Bound_z <<endl;
	vec3 tempPosition;
	bool timeFlag;
	ScreenChange = 1;

	bool monsterTimeFlag;
	int monsterMoveDirection;

	bool jumpTimeFlag;

	QueryPerformanceCounter(&monsterStartTime);
	QueryPerformanceCounter(&jumpStartTime);

	
	TexturePic* image;
	gl_Image imageProcessor;
	int numberOfTexture =43; 

	image = new TexturePic[numberOfTexture];
	//for(int i = 0; i < numberOfTexture;i++){
	image[0].id = imageProcessor.loadImage("Model/Back00.jpg", image[0], 0, Info);
	image[1].id = imageProcessor.loadImage("Model/QBert00.jpg", image[1], 1, Info);
	image[2].id = imageProcessor.loadImage("Model/QBert01.jpg", image[2], 1, Info);
	image[3].id = imageProcessor.loadImage("Model/QBert02.jpg", image[3], 1, Info);
	image[4].id = imageProcessor.loadImage("Model/QBert03.jpg", image[4], 1, Info);
	image[5].id = imageProcessor.loadImage("Model/Monster01.jpg", image[5], 1, Info);
	image[6].id = imageProcessor.loadImage("Model/Monster03.jpg", image[6], 1, Info);
	image[7].id = imageProcessor.loadImage("Model/Monster04.jpg", image[7], 1, Info);
	image[8].id = imageProcessor.loadImage("Model/Monster00.jpg", image[8], 1, Info);
	image[9].id = imageProcessor.loadImage("Model/cry.jpg", image[9], 1, Info);
	image[10].id = imageProcessor.loadImage("Model/spin01.jpg", image[10], 1, Info);
	image[11].id = imageProcessor.loadImage("Model/spin02.jpg", image[11], 1, Info);
	image[12].id = imageProcessor.loadImage("Model/spin03.jpg", image[12], 1, Info);
	image[13].id = imageProcessor.loadImage("Model/num00.jpg", image[13], 1, Info);
	image[14].id = imageProcessor.loadImage("Model/num01.jpg", image[14], 1, Info);
	image[15].id = imageProcessor.loadImage("Model/num02.jpg", image[15], 1, Info);
	image[16].id = imageProcessor.loadImage("Model/num03.jpg", image[16], 1, Info);
	image[17].id = imageProcessor.loadImage("Model/num04.jpg", image[17], 1, Info);
	image[18].id = imageProcessor.loadImage("Model/num05.jpg", image[18], 1, Info);
	image[19].id = imageProcessor.loadImage("Model/num06.jpg", image[19], 1, Info);
	image[20].id = imageProcessor.loadImage("Model/num07.jpg", image[20], 1, Info);
	image[21].id = imageProcessor.loadImage("Model/num08.jpg", image[21], 1, Info);
	image[22].id = imageProcessor.loadImage("Model/num09.jpg", image[22], 1, Info);

	image[23].id = imageProcessor.loadImage("Model/num200.jpg", image[23], 1, Info);
	image[24].id = imageProcessor.loadImage("Model/num201.jpg", image[24], 1, Info);
	image[25].id = imageProcessor.loadImage("Model/num202.jpg", image[25], 1, Info);
	image[26].id = imageProcessor.loadImage("Model/num203.jpg", image[26], 1, Info);
	image[27].id = imageProcessor.loadImage("Model/num204.jpg", image[27], 1, Info);
	image[28].id = imageProcessor.loadImage("Model/num205.jpg", image[28], 1, Info);
	image[29].id = imageProcessor.loadImage("Model/num206.jpg", image[29], 1, Info);
	image[30].id = imageProcessor.loadImage("Model/num207.jpg", image[30], 1, Info);
	image[31].id = imageProcessor.loadImage("Model/num208.jpg", image[31], 1, Info);
	image[32].id = imageProcessor.loadImage("Model/num209.jpg", image[32], 1, Info);
	image[33].id = imageProcessor.loadImage("Model/num2010.jpg", image[33], 1, Info);

	image[34].id = imageProcessor.loadImage("Model/Back00.jpg", image[34], 1, Info);
	image[35].id = imageProcessor.loadImage("Model/Back01.jpg", image[35], 1, Info);
	image[36].id = imageProcessor.loadImage("Model/Back02.jpg", image[36], 1, Info);

	image[37].id = imageProcessor.loadImage("Model/Open00.jpg", image[37], 1, Info);
	image[38].id = imageProcessor.loadImage("Model/start.jpg", image[38], 1, Info);
	image[39].id = imageProcessor.loadImage("Model/exit.jpg", image[39], 1, Info);

	image[40].id = imageProcessor.loadImage("Model/second.jpg", image[40], 1, Info);
	image[41].id = imageProcessor.loadImage("Model/third.jpg", image[41], 1, Info);
	image[42].id = imageProcessor.loadImage("Model/end.jpg", image[42], 1, Info);


	//}

	int standCubeIndex;
	vec3 diffJump;
	spin1Rotate =0;
	int tempangle =0;
	int monsterAnimation =0;
	int monsterJump =0;
	bool monsterJumpFlag;
	gameStatus.printEnd = 0;

	vec3* monsterDifferJump;
	monsterDifferJump = new vec3[numberOfMonster];

	int* monsterTempIndex;
	monsterTempIndex = new int[numberOfMonster];

	monsterNextPosition = new vec3[numberOfMonster];
	monsterLastPosition = new vec3[numberOfMonster];

	LARGE_INTEGER monsterJumpStartTime;
	LARGE_INTEGER monsterJumpEndTime;
	int type3Monster = rand()%4;

	goToNext = 0;
	gameStatus.gameLevel = 0 ;
	gameRoom =0;
	gameStatus.gameRoom = gameRoom;

	display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);

	//int loopCount = 30;
	// Draw loop
	int isOpeningEnd = 0;
	int TransLevel = 0;
	LARGE_INTEGER transStartTime;
	LARGE_INTEGER transEndTime;
	bool transFlag;




	int transJump;

	vec3 transMon1Old = transMon1.currentPosition;
	vec3 transMon2Old =transMon2.currentPosition;
	vec3 transMon3Old =transMon3.currentPosition;

	
	while (glfwGetKey( Window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose( Window ) == 0)
    {
		
		
		imageProcessor.sendTexture(image, Info, numberOfTexture, "texturePic");
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();
		//glOrtho(0.0f, ScreenWidth, ScreenHeight, 0.0f, 0.0f, 1.0f);
		eyePosition = vec3(50.0f, 50.0f, 50.0f);
		platformTranslation = glm::translate ( mat4(), vec3 (0, (gameStatus.gameLevel+5)*1.25 , 0));


	if(gameStatus.gameRoom==0){
		//opening
		//cout << "Game Opening Animation" <<endl;


		eyePosition = vec3(0, 0, 50);
		//gameStatus.gameRoom = (gameStatus.gameRoom+1)% 4;

		if(ReloadData == 1){
			display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);
			ReloadData = (ReloadData+1)%2;
		}

		draw.SetMVP(Info, ScreenWidth, ScreenHeight, ScreenScale, eyePosition, platformTranslation);
		//draw.SendTriangleToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);
		draw.SendDataToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX, Stage, triangleCountVector, currentCubeTotal, numberOfMonster, ScreenChange, gameStatus);
		draw.Draw( Window, Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);


	}
	else if(gameStatus.gameRoom %2 == 1){
		if(goToNext==0){
		//generate new Room
			eyePosition = vec3(50.0f, 50.0f,50.0f);
	
				input.QBert.setTranlation(0, 1.5, 0);
				for(int i =0; i < currentCubeTotal; i++){
					//initial cube state
					input.checkCubeState[i] = 0;
				}
				
				for(int i =0;i < input.cubeList.size();i++){
					if(gameStatus.gameLevel == 0){
						input.cubeList[i].setColor_Front(vec3(16/255.0, 192/255.0, 17/255.0));
						input.cubeList[i].setColor_Right(vec3(82/255.0, 129/255.0, 82/255.0));
						input.cubeList[i].setColor_Top(vec3(0/255.0, 105/255.0, 0/255.0));

					}
					else if(gameStatus.gameLevel == 1){
						input.cubeList[i].setColor_Front(vec3(124/255.0, 223/255.0, 255/255.0));
						input.cubeList[i].setColor_Right(vec3(101/255.0, 158/255.0, 177/255.0));
						input.cubeList[i].setColor_Top(vec3(0/255.0, 99/255.0, 144/255.0));		
					}
					else if(gameStatus.gameLevel == 2){
						input.cubeList[i].setColor_Front(vec3(193/255.0, 157/255.0, 222/255.0));
						input.cubeList[i].setColor_Right(vec3(158/255.0, 130/255.0, 180/255.0));
						input.cubeList[i].setColor_Top(vec3(116/255.0, 0/255.0, 153/255.0));		
					}
				}

				currentCubeTotal = 0;
				needToAchieve =0;

				for(int i =1; i <=gameStatus.gameLevel+5; i++){
					for(int j =1; j <= i; j++){
						currentCubeTotal = currentCubeTotal +j;
					}
					needToAchieve = needToAchieve +i;
				}
				//reset monsters
				monsterUsedList.empty();
				for(int j =0; j <numberOfMonster; j++){
					random =  rand()%(currentCubeTotal-1)+1;
					input.monsterList[j].resetStartPosition(random, currentCubeTotal, cubeList, monsterUsedList);
					monsterUsedList.push_back(input.monsterList[j].startIndex);
					input.monsterList[j].setTranlation(cubeList[input.monsterList[j].startIndex].centerPosition.x,cubeList[input.monsterList[j].startIndex].centerPosition.y+1+(2*0.5/2), cubeList[input.monsterList[j].startIndex].centerPosition.z );
				}

				ReloadData =1;

			goToNext =1;
		}
		//Regular game
	monsterTimeFlag =flexibleTimeDelay(0.1, monsterStartTime, monsterEndTime);
	if(animation ==0 && monsterAnimation == 0){
		if(monsterTimeFlag == true){
			//cout << " a second pass" <<endl;
			if(monsterJump == 0){
				for(int i =0; i < numberOfMonster; i++){
					tempangle = ((int)tempangle+10)%360;
					input.spin1.setRotate((float)tempangle);
					input.spin2.setRotate((float)tempangle);
					monsterMoveDirection = rand()%4;
					monsterLastPosition[i] = input.monsterList[i].currentPosition;
					if(input.monsterList[i].monsterType == 3){
						type3Monster = (type3Monster+1)%4; 
						monsterNextPosition[i] = input.monsterList[i].randomMove(type3Monster, cubeList, currentCubeTotal);
					}
					else{
						monsterNextPosition[i] = input.monsterList[i].randomMove(monsterMoveDirection, cubeList, currentCubeTotal);
					}
					monsterTempIndex[i] = input.monsterList[i].getIndex(cubeList, monsterNextPosition[i], currentCubeTotal);
					//input.monsterList[i].currentIndex = input.monsterList[i].getIndex(cubeList, monsterNextPosition[i], currentCubeTotal);			
					if(monsterTempIndex[i]>0){

					}
					else{
						monsterNextPosition[i] = input.monsterList[i].currentPosition;
					}
				}
			}
			else if(monsterJump ==1){
				for(int i= 0; i< numberOfMonster ;i++){
					monsterDifferJump[i] =monsterNextPosition[i]- monsterLastPosition[i];
					input.monsterList[i].setScale(0.5, 0.4, 0.5);
					input.monsterList[i].setTranlation(monsterLastPosition[i].x, monsterLastPosition[i].y-0.1,monsterLastPosition[i].z);
				}			
			}
			else if(monsterJump ==2){
				for(int i= 0; i< numberOfMonster ;i++){
					monsterDifferJump[i] =monsterNextPosition[i]- monsterLastPosition[i];
					if(monsterDifferJump[i].y!=0){
						input.monsterList[i].setScale(0.5, 0.7, 0.5);
						input.monsterList[i].setTranlation(monsterLastPosition[i].x+(monsterDifferJump[i].x/6), monsterLastPosition[i].y+(monsterDifferJump[i].y/6)+2.5+0.2,monsterLastPosition[i].z+(monsterDifferJump[i].z/4));
					}
				}			
			}
			else if(monsterJump ==3){
				for(int i= 0; i< numberOfMonster ;i++){
					monsterDifferJump[i] =monsterNextPosition[i]- monsterLastPosition[i];
					if(monsterDifferJump[i].y!=0){
						input.monsterList[i].setScale(0.5, 0.8, 0.5);
						input.monsterList[i].setTranlation(monsterLastPosition[i].x+(monsterDifferJump[i].x/6*2), monsterLastPosition[i].y+(monsterDifferJump[i].y/6*2)+3+0.3,monsterLastPosition[i].z+(monsterDifferJump[i].z/6*2));
					}
				}	
	
			}
			else if(monsterJump ==4){
				for(int i= 0; i< numberOfMonster ;i++){
					monsterDifferJump[i] =monsterNextPosition[i]- monsterLastPosition[i];
					if(monsterDifferJump[i].y!=0){
						input.monsterList[i].setScale(0.5, 0.7, 0.5);
						input.monsterList[i].setTranlation(monsterLastPosition[i].x+(monsterDifferJump[i].x/6*3), monsterLastPosition[i].y+(monsterDifferJump[i].y/6*3)+4,monsterLastPosition[i].z+(monsterDifferJump[i].z/6*3));
					}
				}	
	
			}
			else if(monsterJump ==5){
				for(int i= 0; i< numberOfMonster ;i++){
					monsterDifferJump[i] =monsterNextPosition[i]- monsterLastPosition[i];
					if(monsterDifferJump[i].y!=0){
						input.monsterList[i].setScale(0.5, 0.6, 0.5);
						input.monsterList[i].setTranlation(monsterLastPosition[i].x+(monsterDifferJump[i].x/6*4), monsterLastPosition[i].y+(monsterDifferJump[i].y/6*4)+3+0.2,monsterLastPosition[i].z+(monsterDifferJump[i].z/6*4));
					}				
				}	
	
			}
			else if(monsterJump ==6){
				for(int i= 0; i< numberOfMonster ;i++){
					monsterDifferJump[i] =monsterNextPosition[i]- monsterLastPosition[i];
					if(monsterDifferJump[i].y!=0){
						input.monsterList[i].setScale(0.5, 0.4, 0.5);
						input.monsterList[i].setTranlation(monsterLastPosition[i].x+(monsterDifferJump[i].x/6*5), monsterLastPosition[i].y+(monsterDifferJump[i].y/6*5)+2.5-0.1,monsterLastPosition[i].z+(monsterDifferJump[i].z/6*5));
					}				
				}	
	
			}
			monsterJump++;
			if(monsterJump == 7){
				monsterJump =0;
				for(int i =0; i < numberOfMonster; i++){
					//input.monsterList[i].setTranlation(input.monsterList[i].currentPosition.x-0.5,input.monsterList[i].currentPosition.y, input.monsterList[i].currentPosition.z);
					//cout << "move " <<rand()%4 << endl;
					input.monsterList[i].currentIndex = input.monsterList[i].getIndex(cubeList, monsterNextPosition[i], currentCubeTotal);
					if(input.monsterList[i].currentIndex>0){
						input.monsterList[i].setTranlation(monsterNextPosition[i].x, monsterNextPosition[i].y, monsterNextPosition[i].z);
						//cout <<input.monsterList[i].currentIndex <<endl;
						if(input.QBert.currentIndex == input.monsterList[i].currentIndex){
							cout<< "QBert met monster " << input.monsterList[i].monsterIndex << " it should die in cube " << input.QBert.currentIndex << endl;
							animation = 1;
							dead =2;
							gameStatus.printCry =10;
							input.QBert.currentIndex =0;
						}
					}

				}

			}
			QueryPerformanceCounter(&monsterStartTime);
			ReloadData =1;
		}
	}



		if(animation ==1 && jump >=1){
			jumpTimeFlag = flexibleTimeDelay(0.1, jumpStartTime, jumpEndTime);

			if(jumpTimeFlag == true){
			//cout << " a second pass" <<endl;
				jump++;
				if(jump ==1){

					diffJump = nextPosition - lastPosition;
					input.QBert.setScale(0.5, 0.4, 0.5);
					input.QBert.setTranlation(lastPosition.x, lastPosition.y-0.1,lastPosition.z);
				}
				else if(jump ==2){
					diffJump = nextPosition - lastPosition;
					input.QBert.setScale(0.5, 0.7, 0.5);
					input.QBert.setTranlation(lastPosition.x+(diffJump.x/6), lastPosition.y+(diffJump.y/6)+2.5+0.2,lastPosition.z+(diffJump.z/6));
				
				}
				else if(jump ==3){
					diffJump = nextPosition - lastPosition;
					input.QBert.setScale(0.5, 0.8, 0.5);
					input.QBert.setTranlation(lastPosition.x+(diffJump.x/6*2), lastPosition.y+(diffJump.y/6*2)+3+0.3,lastPosition.z+(diffJump.z/6*2));				
				}
				else if(jump ==4){
					diffJump = nextPosition - lastPosition;
					input.QBert.setScale(0.5, 0.7, 0.5);
					input.QBert.setTranlation(lastPosition.x+(diffJump.x/6*3), lastPosition.y+(diffJump.y/6*3)+4,lastPosition.z+(diffJump.z/6*3));					
				}
				else if(jump ==5){
					diffJump = nextPosition - lastPosition;
					input.QBert.setScale(0.5, 0.6, 0.5);
					input.QBert.setTranlation(lastPosition.x+(diffJump.x/6*4), lastPosition.y+(diffJump.y/6*4)+3+0.2,lastPosition.z+(diffJump.z/6*4));					
				}
				else if(jump ==6){
					diffJump = nextPosition - lastPosition;
					input.QBert.setScale(0.5, 0.4, 0.5);
					input.QBert.setTranlation(lastPosition.x+(diffJump.x/6*5), lastPosition.y+(diffJump.y/6*5)+2.5-0.1,lastPosition.z+(diffJump.z/6*5));					
				}

				if(jump >=7){
					input.QBert.setTranlation(nextPosition.x, nextPosition.y, nextPosition.z);
					jump = 0;
					animation =0;
					standCubeIndex = checkPosition(input.cubeList, input.QBert.currentPosition);
					if(standCubeIndex < 0){
						//cout << "jump out" << endl;
						animation = 1;
						dead = 1;
					}
					else
					{
						//cout << "On cube " << standCubeIndex << endl; 
						//cout << "Center Position = (" << input.cubeList[standCubeIndex].centerPosition.x
						//	                    <<", "<< input.cubeList[standCubeIndex].centerPosition.y
						//						<<", "<< input.cubeList[standCubeIndex].centerPosition.z << ")" << endl;

						for(int i =0; i< numberOfMonster; i++){
							if(input.QBert.currentIndex == input.monsterList[i].currentIndex){
							cout<< "QBert met monster " << input.monsterList[i].monsterIndex << " it should die in cube " << input.QBert.currentIndex << endl;
							
							animation = 1;
							dead =2;
							gameStatus.printCry =10;
							input.QBert.currentIndex =0;

							}	
						}

						if(standCubeIndex >=0 && standCubeIndex <= currentCubeTotal){

							if(input.checkCubeState[standCubeIndex] == 0){
							
								input.cubeList[standCubeIndex].setColor_Top(vec3(1-input.cubeList[standCubeIndex].colorTop.r,1-input.cubeList[standCubeIndex].colorTop.g, 1-input.cubeList[standCubeIndex].colorTop.b));
								input.checkCubeState[standCubeIndex] = 1;
								gameStatus.score = gameStatus.score+10;
								gameStatus.updateNumber();
								//cout << "current score: " <<gameStatus.score << endl;
							}
						}

					}


				}
				QueryPerformanceCounter(&jumpStartTime);
				ReloadData =1;

			}

		
		}


		if(animation == 1 && dead == 1){
			timeFlag = timeDelay(0.05);
			if(timeFlag == true){
				//cout << " a second pass" <<endl;
				tempPosition = input.QBert.currentPosition;
				//cout << "falling " << tempPosition.y-0.5 << ", " << Bound_y << endl;
				input.QBert.setTranlation(tempPosition.x, tempPosition.y-0.5, tempPosition.z);
				//cout << "falling " << tempPosition.y-0.5 << ", " << Bound_y << endl;
				ReloadData = 1;
				if(tempPosition.y-0.5 < Bound_y-10){
					//cout << "falling " << tempPosition.y-0.5 << ", " << Bound_y << endl;
					animation = 0;
					dead = 0;
					gameStatus.lives = gameStatus.lives-1;
					if(gameStatus.lives == 0){
						gameStatus.gameRoom =7;
						ReloadData = 1;
						gameStatus.printEnd =1;




						if(ReloadData == 1){
							display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);
							ReloadData = (ReloadData+1)%2;
						}

						draw.SetMVP(Info, ScreenWidth, ScreenHeight, ScreenScale, eyePosition, platformTranslation);
						//draw.SendTriangleToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);
						draw.SendDataToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX, Stage, triangleCountVector, currentCubeTotal, numberOfMonster, ScreenChange, gameStatus);
						draw.Draw( Window, Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);

					}

					input.QBert.setTranlation(0, 1.5, 0);
				}
				timeFlag = false;
				QueryPerformanceCounter(&startTime);
			}

		
		}
		if(animation == 1 && dead == 2){
			timeFlag = timeDelay(0.05);
			if(timeFlag == true){
				//cout << " a second pass" <<endl;
				tempPosition = input.QBert.currentPosition;
				//cout << "falling " << tempPosition.y-0.5 << ", " << Bound_y << endl;
				//input.QBert.setTranlation(tempPosition.x, tempPosition.y-0.5, tempPosition.z);
				input.cry.setTranlation(tempPosition.x, tempPosition.y+2, tempPosition.z);

				//cout << "falling " << tempPosition.y-0.5 << ", " << Bound_y << endl;
				gameStatus.printCry--;
				if(gameStatus.printCry <=0){
					//cout << "falling " << tempPosition.y-0.5 << ", " << Bound_y << endl;
					animation = 0;
					dead = 0;
					gameStatus.lives = gameStatus.lives-1;
					if(gameStatus.lives == 0){
						gameStatus.gameRoom =7;
						ReloadData =1;
						gameStatus.printEnd =1;

						if(ReloadData == 1){
							display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);
							ReloadData = (ReloadData+1)%2;
						}

						draw.SetMVP(Info, ScreenWidth, ScreenHeight, ScreenScale, eyePosition, platformTranslation);
						//draw.SendTriangleToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);
						draw.SendDataToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX, Stage, triangleCountVector, currentCubeTotal, numberOfMonster, ScreenChange, gameStatus);
						draw.Draw( Window, Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);



					}
					input.QBert.setTranlation(0, 1.5, 0);

					//gameStatus.printCry =0;
				
				}
				ReloadData = 1;
				timeFlag = false;
				QueryPerformanceCounter(&startTime);
			}

		
		}
		if(ReloadData == 1){
			//When something change
			//input.cubeList[3].setColor_Top(vec3(1.0, 0.0, 0.0));
			//cout<< cubeList.size() << endl;
			display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);
			ReloadData = (ReloadData+1)%2;

			checkWin();
			/*
			timeFlag = timeDelay(0.1);
			if(timeFlag == true){
				
				QueryPerformanceCounter(&startTime);
			}
			*/
		}


		draw.SetMVP(Info, ScreenWidth, ScreenHeight, ScreenScale, eyePosition, platformTranslation);
		//draw.SendTriangleToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);
		draw.SendDataToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX, Stage, triangleCountVector, currentCubeTotal, numberOfMonster, ScreenChange, gameStatus);
		draw.Draw( Window, Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);

		if(win == 1 && animation ==1 ){
		//	timeFlag = timeDelay(0.1);
		//	if(timeFlag == true){
				cout << "Win!!!!" << endl;

				//cout << "Level " << Stage <<", currentTotal " << currentCubeTotal << ", need to achieve " << needToAchieve <<endl;
				cout<< gameStatus.gameLevel <<endl; 
				goToNext = 0;
				win = 0;
				animation = 0;
								
				gameStatus.gameLevel= (gameStatus.gameLevel+1)%3;
				gameStatus.gameRoom =(gameStatus.gameRoom +1); 
				Stage = ((Stage-3)+1)%(numberOfPlatformLayer-3)+3;
				
				QueryPerformanceCounter(&transStartTime);
				transJump =1;


		//	}
		}


	}
	else if(gameStatus.gameRoom%2 == 0 && gameStatus.gameRoom != 0){
		//cout<< "level trans animation for level " << gameStatus.gameLevel; 
		animation =0;
		gameStatus.printCry = 0;
		dead =0;

		eyePosition = vec3(0.0f, 0.0f,50.0f);
		
		if(transJump >=1){
			transFlag = flexibleTimeDelay(0.2, transStartTime, transEndTime);
			if(transFlag == true){
			
				if(transJump ==1){

					input.transMon1.setTranlation(transMon1Old.x, transMon1Old.y, transMon1Old.z);
				}
				else if(transJump ==2){
					//input.transMon1.setRotate(90);
					input.transMon1.setScale(1,0.6,1);

				}
				else if(transJump ==3){
					
					
					input.transMon1.setScale(1,1,1);
					input.transMon1.setTranlation(transMon1Old.x+2, transMon1Old.y+3, transMon1Old.z);

					input.transMon2.setScale(1,1,1);
					input.transMon2.setTranlation(transMon1Old.x-2, transMon1Old.y+3, transMon1Old.z);

					input.transMon3.setScale(1,1,1);
					input.transMon3.setTranlation(transMon1Old.x+2, transMon1Old.y+3, transMon1Old.z);

				}
				else if(transJump ==4){
					input.transMon1.setScale(1,1.2,1);
					input.transMon1.setTranlation(transMon1Old.x+4, transMon1Old.y+5, transMon1Old.z);

					input.transMon2.setScale(1,1.2,1);
					input.transMon2.setTranlation(transMon1Old.x-4, transMon1Old.y+5, transMon1Old.z);

					input.transMon3.setScale(1,1.2,1);
					input.transMon3.setTranlation(transMon1Old.x+4, transMon1Old.y+5, transMon1Old.z);

				}
				else if(transJump ==5){
					input.transMon1.setScale(1,1,1);
					input.transMon1.setTranlation(transMon1Old.x+6, transMon1Old.y+5, transMon1Old.z);

					input.transMon2.setScale(1,1,1);
					input.transMon2.setTranlation(transMon1Old.x-6, transMon1Old.y+5, transMon1Old.z);

					input.transMon3.setScale(1,1,1);
					input.transMon3.setTranlation(transMon1Old.x+6, transMon1Old.y+5, transMon1Old.z);

				}
				else if(transJump ==6){
					input.transMon1.setScale(1,0.8,1);
					input.transMon1.setTranlation(transMon1Old.x+8, transMon1Old.y+3, transMon1Old.z);

					input.transMon2.setScale(1,0.8,1);
					input.transMon2.setTranlation(transMon1Old.x-8, transMon1Old.y+3, transMon1Old.z);

					input.transMon3.setScale(1,0.8,1);
					input.transMon3.setTranlation(transMon1Old.x+6, transMon1Old.y+3, transMon1Old.z);

				}
				else if(transJump ==7){
					input.transMon1.setScale(1,0.5,1);
					input.transMon1.setTranlation(transMon1Old.x+10, transMon1Old.y, transMon1Old.z);

					input.transMon2.setScale(1,0.5,1);
					input.transMon2.setTranlation(transMon1Old.x-10, transMon1Old.y, transMon1Old.z);
					input.transMon3.setScale(1,0.5,1);
					input.transMon3.setTranlation(transMon1Old.x+4, transMon1Old.y, transMon1Old.z);

				}
				else if(transJump ==8){

					//input.transMon1.setRotate(0);
					input.transMon1.setScale(1,0.7,1);
					input.transMon1.setTranlation(transMon1Old.x+10, transMon1Old.y-3, transMon1Old.z);

					input.transMon2.setScale(1,0.7,1);
					input.transMon2.setTranlation(transMon1Old.x-10, transMon1Old.y-3, transMon1Old.z);

					input.transMon3.setScale(1,0.7,1);
					input.transMon3.setTranlation(transMon1Old.x, transMon1Old.y-3, transMon1Old.z);

				}
				else if(transJump ==9){
					
					//input.transMon1.setRotate(0);
					input.transMon1.setScale(1,1,1);
					input.transMon1.setTranlation(transMon1Old.x+10, transMon1Old.y-6, transMon1Old.z);

					input.transMon2.setScale(1,1,1);
					input.transMon2.setTranlation(transMon1Old.x-10, transMon1Old.y-4, transMon1Old.z);

					input.transMon3.setScale(1,1,1);
					input.transMon3.setTranlation(transMon1Old.x-2, transMon1Old.y-3, transMon1Old.z);

				}
				transJump++;
				if(transJump >=18){
					transJump = 0;
					gameStatus.gameRoom =(gameStatus.gameRoom +1);

				}

				QueryPerformanceCounter(&transStartTime);
				ReloadData =1;
			}
		}
	
		
		if(ReloadData == 1){
			display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);
			ReloadData = (ReloadData+1)%2;
		}

		draw.SetMVP(Info, ScreenWidth, ScreenHeight, ScreenScale, eyePosition, platformTranslation);
		//draw.SendTriangleToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);
		draw.SendDataToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX, Stage, triangleCountVector, currentCubeTotal, numberOfMonster, ScreenChange, gameStatus);
		draw.Draw( Window, Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);
	}
	
	
	
	if(gameStatus.gameRoom>5){
		//cout << "program end" << endl;
		//cout << "ending animation" <<endl;
		animation =1;
		goToNext =1;
		gameStatus.gameRoom++;
		gameStatus.printEnd = 1;


		if(ReloadData == 1){
			display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);
			ReloadData = (ReloadData+1)%2;
		}

		draw.SetMVP(Info, ScreenWidth, ScreenHeight, ScreenScale, eyePosition, platformTranslation);
		//draw.SendTriangleToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);
		draw.SendDataToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX, Stage, triangleCountVector, currentCubeTotal, numberOfMonster, ScreenChange, gameStatus);
		draw.Draw( Window, Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);

		//break;

	}

		if(ReloadData == 1){
			display.InitInfo(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, input, triangleCountVector, numberOfMonster, gameStatus);
			ReloadData = (ReloadData+1)%2;
		}	
		draw.SetMVP(Info, ScreenWidth, ScreenHeight, ScreenScale, eyePosition, platformTranslation);
		//draw.SendTriangleToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);
		draw.SendDataToShader(Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX, Stage, triangleCountVector, currentCubeTotal, numberOfMonster, ScreenChange, gameStatus);
		draw.Draw( Window, Info, numberOfTriangles, NUMBER_OF_VERTEX_PER_TRI, NUMBER_OF_FLOAT_PER_VERTEX);

}


	//cout<< "out time loop" << endl;
	// Terminate Window
	display.End( Window );



	system("pause");
	return 0;
}
int GeneratePlatform(vector<QBert_Cube> &cubeList, int const numberOfPlatformLayer){
	int numberOfTriangles;
	int currentLevel;
	int numberOfCubes;

	int tempState;


	cubeList.empty();
	QBert_Cube tempCube;
	int currentCubeIndex = 0;
	currentLevel = Stage;

	vec3 startPoint = vec3(0,0,0);


	for(int i = 1; i <= numberOfPlatformLayer ; i++){
		tempCube = QBert_Cube();
		for(int j= 1; j <= i; j++){
			for(int k =j; k<= i; k++){
				//x = j -1
				//y = i -1
				//z = i - k 
				tempCube.setColor_Front(vec3(16/255.0, 192/255.0, 17/255.0));
				tempCube.setColor_Right(vec3(82/255.0, 129/255.0, 82/255.0));
				tempCube.setColor_Top(vec3(0/255.0, 105/255.0, 0/255.0));

				tempCube.setTranlation(startPoint.x+(j-1)*(2), startPoint.y+(i-1)*(-2), startPoint.z+(i-k)*(2));
				
				tempState = 0;
				//cout<< "cube " << currentCubeIndex << " ";
				//cout <<"shift (" << startPoint.x+(j-1)
				//	       <<", "<< startPoint.y+(i-1)
				//		   <<", "<< startPoint.z+(i-k) << " )" <<endl; 
				tempCube.index = currentCubeIndex;
				currentCubeIndex++;

				cubeList.push_back(tempCube);
				checkCubeState.push_back(tempState);
			}
		}

	}
	//cout << "total cube number = " << currentCubeIndex << endl;
	numberOfCubes = currentCubeIndex;
	numberOfTriangles = numberOfCubes * 12;

	return numberOfTriangles;
}
int GenerateMonter(vector<QBert_Cube_Monster> &monsterList, int numberOfMonster){
	int numberOfTriangles;

	int type;
	int position;
	int random;
	QBert_Cube_Monster tempMonster;
	monsterUsedList.empty();

	srand (time(NULL));
	//different types of monsters
	for(int i = 0; i<numberOfMonster ; i++){
		tempMonster.monsterIndex = i;
		//type = rand()%3;
		type =i;
		tempMonster.monsterType = type;
		//cout << rand()%(currentCubeTotal-1)+1 <<endl;
		random =  rand()%(currentCubeTotal-1)+1;
		if(type == 0){
			//tempMonster.setBaseNumber(6);
			tempMonster.textureBaseNumber =6;
			tempMonster.setAllColor(vec3(142.0/255.0,238.0/255.0, 255.0/255.0));
			tempMonster.setScale(0.5,0.5,0.5);
			//cout << "***" << currentCubeTotal << endl;
			tempMonster.resetStartPosition(random, currentCubeTotal, cubeList, monsterUsedList);
			monsterUsedList.push_back(tempMonster.startIndex);
			tempMonster.setTranlation(cubeList[tempMonster.startIndex].centerPosition.x,cubeList[tempMonster.startIndex].centerPosition.y+1+(2*0.5/2), cubeList[tempMonster.startIndex].centerPosition.z );
			//tempMonstor.setTranslation(input.cubeList[]);
		}
		else if(type == 1){
			//tempMonster.setBaseNumber(7);
			tempMonster.textureBaseNumber =7;
			
			tempMonster.setAllColor(vec3(175.0/255.0,255.0/255.0, 157.0/255.0));
			tempMonster.setScale(0.5,0.5,0.5);
			//cout << "***" << currentCubeTotal << endl;
			tempMonster.resetStartPosition(random, currentCubeTotal, cubeList, monsterUsedList);
			monsterUsedList.push_back(tempMonster.startIndex);
			tempMonster.setTranlation(cubeList[tempMonster.startIndex].centerPosition.x,cubeList[tempMonster.startIndex].centerPosition.y+1+(2*0.5/2), cubeList[tempMonster.startIndex].centerPosition.z );
		}
		else if(type == 2){
			//tempMonster.setBaseNumber(8);
			tempMonster.textureBaseNumber =8;
			
			tempMonster.setAllColor(vec3(246.0/255.0,223.0/255.0, 121.0/255.0));
			tempMonster.setScale(0.5,0.5,0.5);
			//cout << "***" << currentCubeTotal << endl;
			tempMonster.resetStartPosition(random, currentCubeTotal, cubeList, monsterUsedList);
			monsterUsedList.push_back(tempMonster.startIndex);
			tempMonster.setTranlation(cubeList[tempMonster.startIndex].centerPosition.x,cubeList[tempMonster.startIndex].centerPosition.y+1+(2*0.5/2), cubeList[tempMonster.startIndex].centerPosition.z );
		}
		else if(type == 3){
			//tempMonster.setBaseNumber(8);
			tempMonster.textureBaseNumber =9;
			
			tempMonster.setAllColor(vec3(2550/255.0,145.0/255.0, 171.0/255.0));
			tempMonster.setScale(0.5,0.5,0.5);
			//cout << "***" << currentCubeTotal << endl;
			tempMonster.resetStartPosition(random, currentCubeTotal, cubeList, monsterUsedList);
			monsterUsedList.push_back(tempMonster.startIndex);
			tempMonster.setTranlation(cubeList[tempMonster.startIndex].centerPosition.x,cubeList[tempMonster.startIndex].centerPosition.y+1+(2*0.5/2), cubeList[tempMonster.startIndex].centerPosition.z );
		}

		monsterList.push_back(tempMonster);
		triangleCountVector.push_back(tempMonster.numberOfTriangle);
	
	}



	return numberOfTriangles;
}
int GenerateItem(vector<QBert_Cube_Monster> &itemList){
	int numberOfTriangles;
	return numberOfTriangles;
}

void KeyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	vec3 tempPosition;

	int standCubeIndex;

	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS){
        glfwSetWindowShouldClose(Window, GL_TRUE);
		endFlag = true;
	}
	if (Key == GLFW_KEY_SPACE && Action == GLFW_PRESS){
        ScreenChange ++;
	}
	//QBert move
	if(Key == GLFW_KEY_LEFT && Action == GLFW_PRESS){
		tempPosition = input.QBert.currentPosition;

		if(animation == 0){
			//input.QBert.setTranlation(tempPosition.x-2, tempPosition.y+2, tempPosition.z);
			nextPosition = vec3(tempPosition.x-2, tempPosition.y+2, tempPosition.z);
			lastPosition = input.QBert.currentPosition;
			animation =1;
			jump =1;
			input.QBert.setRotate(-90);

			ReloadData = 1;
		}
	}
	if(Key == GLFW_KEY_RIGHT && Action == GLFW_PRESS){
		tempPosition = input.QBert.currentPosition;
		if(animation == 0){

			nextPosition = vec3(tempPosition.x+2, tempPosition.y-2, tempPosition.z);
			lastPosition = input.QBert.currentPosition;
			animation =1;
			jump =1;

			input.QBert.setRotate(90);
			ReloadData = 1;
		}
	}
	if(Key == GLFW_KEY_UP && Action == GLFW_PRESS){

		if(gameStatus.gameRoom ==0){
			input.openingButton.setTranlation(-0.3, 0.2, 0);
			ReloadData = 1;
		}
		else{
			tempPosition = input.QBert.currentPosition;
			if(animation == 0){

				nextPosition = vec3(tempPosition.x, tempPosition.y+2, tempPosition.z-2);
				lastPosition = input.QBert.currentPosition;
				animation =1;
				jump =1;

				input.QBert.setRotate(180);
				ReloadData = 1;
			}
		}

	}
	if(Key == GLFW_KEY_DOWN && Action == GLFW_PRESS){
		
		if(gameStatus.gameRoom ==0){
			input.openingButton.setTranlation(-0.3, -0.2, 0);
			ReloadData = 1;
		}
		else{		
			tempPosition = input.QBert.currentPosition;
			if(animation == 0){
				nextPosition = vec3(tempPosition.x, tempPosition.y-2, tempPosition.z+2);
				lastPosition = input.QBert.currentPosition;
				animation =1;
				jump =1;

				input.QBert.setRotate(0);
				ReloadData = 1;
			}
		}

	}

	if(Key == GLFW_KEY_LEFT_CONTROL && Action == GLFW_PRESS){
		if(gameStatus.gameRoom==0){
			gameStatus.gameRoom =gameStatus.gameRoom+1;
		}
		else{
			animation =1;
			win =1;
		}
	}

	if(Key == GLFW_KEY_ENTER && Action == GLFW_PRESS){
		if(input.openingButton.currentPosition.y == input.openingStart.currentPosition.y){
			gameStatus.gameRoom = gameStatus.gameRoom+1;
		}
		else{
			gameStatus.gameRoom = 6;
		}
	}

}

bool timeDelay(double delay){
	double times;
    QueryPerformanceFrequency(&fre);
	QueryPerformanceCounter(&endTime);

	times=((double)endTime.QuadPart-(double)startTime.QuadPart)/fre.QuadPart;
	if(times > delay){
		return true;
	}
	else{
		return false;
	}
}
bool flexibleTimeDelay(double delay, LARGE_INTEGER &inputStartTime, LARGE_INTEGER &inputEndTime){
	double times;
    QueryPerformanceFrequency(&fre);
	QueryPerformanceCounter(&inputEndTime);

	times=((double)inputEndTime.QuadPart-(double)inputStartTime.QuadPart)/fre.QuadPart;
	if(times > delay){
		return true;
	}
	else{
		return false;
	}
}
int checkPosition(vector<QBert_Cube> &cubeList, vec3 objectPosition){

	int i =0;
	while (i < currentCubeTotal){
		//cout <<"checking cube " << input.cubeList[i].index << endl;
		if(objectPosition.x == cubeList[i].centerPosition.x && objectPosition.z == cubeList[i].centerPosition.z && objectPosition.y - cubeList[i].centerPosition.y < 2){
			//cout<< "On cube " << i<< endl;
			input.QBert.currentIndex = i;
			return i;
		}
		else{
			i++;
		}
	}
	//check spins

	if(objectPosition.x == spinList[0].currentPosition.x && objectPosition.z == spinList[0].currentPosition.z && objectPosition.y - spinList[0].currentPosition.y < 2){
			//cout<< "On cube " << i<< endl;
		input.QBert.currentIndex = 1000;
		return 1000;
	}
	if(objectPosition.x == spinList[1].currentPosition.x && objectPosition.z == spinList[1].currentPosition.z && objectPosition.y - spinList[1].currentPosition.y < 2){
			//cout<< "On cube " << i<< endl;
		input.QBert.currentIndex = 1001;
		return 1001;
	}

	//cout << "Out " << endl;
	return -1;
}
void checkWin(){
	int i =0;
	int count = 0;
	while (i < currentCubeTotal){
		//cout <<"checking cube " << input.cubeList[i].index << endl;
		if(input.checkCubeState[i]==1){
			count++;
		}
		i++;
	}
	if(count == needToAchieve){
		win = 1;
		animation =1;
		QueryPerformanceCounter(&startTime);

		//cout << "Win!!!" << endl;
	}
	//cout << "Out " << endl;
	//return -1;
}