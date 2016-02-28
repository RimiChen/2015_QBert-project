/*===============
standrad library
=================*/
#include "standard_library.h"

/*===============
3rd party library
=================*/
#include "3rd_party.h";

#ifndef H_SELF_DEFINED_STRUCTURES
#define H_SELF_DEFINED_STRUCTURES
struct Matrix4f {
    float m[4][4];
};
struct Matrix3f {
    float m[3][3];
};
struct ShaderInfo {
	GLuint programId;
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint colorArray;
	GLuint colorBuffer;
	GLuint uvArray;
	GLuint uvBuffer;
	GLuint constantArray;
	GLuint constantBuffer;
};
struct Point{
	int vertexIndex;
	int vtIndex;
	int vnIndex;
};
struct Face{
	int materialIndex;
	Point vertex[3];
};
struct NewMaterial{
	int index;
	string materialName;
	int offset;
	// parameters
	float Ns;
	float Ni;
	float d;
	float Tr;
	vec3 Tf;
	int illum;
	int mask;
	vec3 Kd;
	vec3 Ks;
	vec3 Ka;
	string map_Kd;
	string map_bump;
	string bump;
	string map_opacity;
	float refl;
	string map_kS;
	string map_kA;
	string map_Ns;
	string map_d;
	vec3 ke;

};
struct GraphicAtom {
	string objFilePath;
	int materialOffset;
	int TransformOffset;
	GLuint numberOfTriangle;
	vector<vec3> vertexVector;
	vector<vec3> vnVector;
	vector<vec2> uv;
	vector<Face> facesOfObject;
	vector<NewMaterial> materialVector;
	string materialFile;
};
struct HierachyObjectTreeNode{
	int nodeIndex;
	int levelNumber;
	//string objName;
	int objIndex;
	Matrix4f tranformMatrix;
	mat4 finalTransform;

	// tree pointer (implemented with array)
	int paraentIndex;
	vector<int> childIndex;
	GraphicAtom selfAtom;
	vector<vec3> box;
	vector<vec3> boxFace;

};
struct RenderNode{
	int hierachyNodeIndex;
	mat4 transformation;
};
struct TexturePic{
	int width;
	int height;
	GLuint id;
	GLint index;
	GLuint textureID;
	GLuint samplerID;
	//unsigned char* image;
	// parameters
};
struct  BoundingBoX{
	vec3 RightUpFront;
	vec3 RightUpBack;
	vec3 RightDownFront;
	vec3 RightDownBack;

	vec3 LeftUpFront;
	vec3 LeftUpBack;
	vec3 LeftDownFront;
	vec3 LeftDownBack;

};
struct  TextFont{
	vector<vec2> vertex;
	vector<vec2> uv;
};
#endif