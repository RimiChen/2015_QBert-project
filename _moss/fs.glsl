#version 330 core

// input color
//in vec3 fragmentColor;
in vec3 uv;
in vec3 textureNumber;
in vec3 vertexColor;


uniform sampler2D texturePic[50];

out vec3 color;

void main() {
	if(ceil(uv.z-0.00001) == 0){
		color = vertexColor;
	}
	else if(ceil(uv.z-0.00001) == 1){
		color = texture( texturePic[0], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 2){
		color = texture( texturePic[1], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 3){
		color = texture( texturePic[2], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 4){
		color = texture( texturePic[3], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 5){
		color = texture( texturePic[4], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 6){
		color = texture( texturePic[5], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 7){
		color = texture( texturePic[6], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 8){
		color = texture( texturePic[7], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 9){
		color = texture( texturePic[8], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 10){
		color = texture( texturePic[9], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 11){
		color = texture( texturePic[10], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 12){
		color = texture( texturePic[11], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 13){
		color = texture( texturePic[12], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 14){
		color = texture( texturePic[13], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 15){
		color = texture( texturePic[14], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 16){
		color = texture( texturePic[15], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 17){
		color = texture( texturePic[16], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 18){
		color = texture( texturePic[17], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 19){
		color = texture( texturePic[18], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 20){
		color = texture( texturePic[19], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 21){
		color = texture( texturePic[20], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 22){
		color = texture( texturePic[21], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 23){
		color = texture( texturePic[22], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 24){
		color = texture( texturePic[23], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 25){
		color = texture( texturePic[24], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 26){
		color = texture( texturePic[25], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 27){
		color = texture( texturePic[26], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 28){
		color = texture( texturePic[27], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 29){
		color = texture( texturePic[28], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 30){
		color = texture( texturePic[29], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 31){
		color = texture( texturePic[30], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 32){
		color = texture( texturePic[31], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 33){
		color = texture( texturePic[32], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 34){
		color = texture( texturePic[33], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 35){
		color = texture( texturePic[34], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 36){
		color = texture( texturePic[35], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 37){
		color = texture( texturePic[36], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 38){
		color = texture( texturePic[37], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 39){
		color = texture( texturePic[38], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 40){
		color = texture( texturePic[39], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 41){
		color = texture( texturePic[40], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 42){
		color = texture( texturePic[41], uv.xy).rgb;
	}
	else if(ceil(uv.z-0.00001) == 43){
		color = texture( texturePic[42], uv.xy).rgb;
	}
}