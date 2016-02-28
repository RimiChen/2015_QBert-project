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
#include "InputData.h"
#include "Status.h"

// tags to avoid duplicated include
#ifndef H_GL_DISPLAY
#define H_GL_DISPLAY

//define class here
class gl_Display{
//public methods
public:

bool Init(GLFWwindow* &Window, int ScreenWidth, int ScreenHeight, string WindowTitle);
bool InitInfo( ShaderInfo &Info, int NumberOfTriangle, int VertexPerTriangle, InputData input, vector<int> triangleNumberCount, int numberOfMonster, GameStatus &gameStatus);
void deleteLastLevel(ShaderInfo &Info);
GLuint InitShader( const char* vertex_file_path, const char* fragment_file_path );

bool End(GLFWwindow* &Window);

//private variables and methods

};

#endif