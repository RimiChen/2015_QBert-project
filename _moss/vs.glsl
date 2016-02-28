#version 330 core

// input vertex data, different for all executions of this shader.
layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 color;
layout( location = 2 ) in vec3 vertexUV;
layout( location = 3 ) in vec3 constantField;



out vec3 vertexColor;
out vec3 uv;

uniform mat4 MVP;

void main() {
 vertexColor = color;
 uv = vertexUV;

 if(constantField.x == 0.0){
	gl_Position = MVP * vec4(position, 1.0f);
 }
 else if(constantField.x ==1.0){
	gl_Position = vec4(position, 1.0f);
 }

}