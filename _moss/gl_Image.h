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

#ifndef H_GL_IMAGE
#define H_GL_IMAGE

//define class here
class gl_Image{
//public methods
public:
GLuint loadImage(string Path, TexturePic &Image, GLint Index, ShaderInfo &Info); 
void sendTexture(TexturePic* &Image, ShaderInfo &Info, int NumberOfTexture, string InitString); 
//private variables and methods
void loadAllMaterials(ShaderInfo &Info, vector<GraphicAtom> &atoms, TexturePic* &Image);

void sendMaterialData(ShaderInfo &Info, vector<GraphicAtom> &atoms, TexturePic* &Image);
};
#endif