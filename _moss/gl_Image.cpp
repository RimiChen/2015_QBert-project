#include "gl_Image.h"
/*
void gl_Image::loadImage(string Path, TexturePic &Image, GLint Index, ShaderInfo &Info){
	
	Image.index = Index;
	//glActiveTexture(GL_TEXTURE0);
	//glGenTextures(1,&Image.id);
	glBindTexture(GL_TEXTURE_2D, Image.id);
	//load image
	unsigned char* image =
		SOIL_load_image(Path.c_str(), &Image.width, &Image.height, 0, SOIL_LOAD_RGB);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Image.width, Image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	//do outside
	//glUniform1i(glGetUniformLocation(Info.programId, "texKitten"), 0);
}
*/


GLuint gl_Image::loadImage(string Path, TexturePic &Image, GLint Index, ShaderInfo &Info){
	
	Image.index = Index;
    // Load and create a texture 
    unsigned char* image;
    // ===================
    // Texture 2
    // ===================
	//glEnable(GL_TEXTURE_2D);
	GLuint id;
	glGenTextures(1, &Image.textureID);
	//glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, Image.textureID);
	glGenSamplers(1, &Image.samplerID);

    //glBindTexture(GL_TEXTURE_2D, Image.id);
	//glDisable(GL_TEXTURE_2D);
    // Set our texture parameters
	glSamplerParameteri(Image.samplerID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(Image.samplerID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load, create texture and generate mipmaps
    image = SOIL_load_image(Path.c_str(), &Image.width, &Image.height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Image.width, Image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
	// glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	//glDeleteTextures(1, &Image.id);
	return id;

}
void gl_Image::sendTexture(TexturePic* &Image, ShaderInfo &Info, int NumberOfTexture, string InitString){
	int textUnit;	
	string textureString;

	for( textUnit=0; textUnit<NumberOfTexture; textUnit++){
		textureString = InitString;
		textureString.append("["+to_string(textUnit)+"]");
		//cout << textureString <<endl;
		//glEnable(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0+textUnit);

		glBindTexture(GL_TEXTURE_2D,  Image[textUnit].textureID);
		glBindSampler(textUnit,  Image[textUnit].samplerID);
		glUniform1i(glGetUniformLocation(Info.programId, textureString.c_str()), textUnit);
		glDisable(GL_TEXTURE_2D);

	}
}
