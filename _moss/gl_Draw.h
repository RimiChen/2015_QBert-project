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
#include "Status.h"

// tags to avoid duplicated include
#ifndef H_GL_DRAW
#define H_GL_DRAW

//define class here
class gl_Draw{
//public methods
public:
mat4 currentMVPMatrix;
bool Draw(GLFWwindow* &Window, ShaderInfo &Info, GLuint NumberOfTriangles, const uint NumberOfVertex, const uint NumberOfFloat);
void SendDataToShader(ShaderInfo &Info, GLuint NumberOfTriangles, const uint NumberOfVertex, const uint NumberOfFloat, int Stage, vector<int> TriangleCount, int currentCubeTotal, int numberOfMonster, int screenChange,GameStatus &gameStatus);
void SendTriangleToShader(ShaderInfo &Info, GLuint NumberOfTriangles, const uint NumberOfVertex, const uint NumberOfFloat);
void SetMVP(ShaderInfo &Info, GLuint const ScreenWidth, GLuint const ScreenHeight, GLuint const ScreenScale, vec3 eyePosition, mat4 const platformTranslation);

};

#endif