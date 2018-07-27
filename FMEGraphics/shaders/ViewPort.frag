#version 330 core

in vec2 TexCoords;
out vec4 color;

#define MAX_TEXTURES 2


struct ViewPortParams
{
	vec4 textureCropParams; // (x, y, width, height)
	vec4 texturePositionParams; // (x, y, widthScale, heightScale)
};

uniform ViewPortParams viewPortParams[MAX_TEXTURES];
uniform int viewPortParamsNum;

uniform sampler2D Texture0;
uniform sampler2D Texture1;


void main()
{    
	float x0 = viewPortParams[0].textureCropParams.x;
	float y0 = viewPortParams[0].textureCropParams.y;
	float wid0 = viewPortParams[0].textureCropParams.z;
	float heig0 = viewPortParams[0].textureCropParams.w;

	float xPos0 = viewPortParams[0].texturePositionParams.x;
	float yPos0 = viewPortParams[0].texturePositionParams.y;
	float widPos0 = viewPortParams[0].texturePositionParams.z;
	float heigPos0 = viewPortParams[0].texturePositionParams.w;
	vec4 color0 = vec4(0.0, 0.0, 0.0, 0.0);


	if((TexCoords.x > x0) && (TexCoords.x < x0 + wid0) && (TexCoords.y > y0) && (TexCoords.y < y0 +  heig0))
	{
		vec2 scaledTexCorrds = vec2(widPos0 * TexCoords.x + xPos0 - x0, heig0 * TexCoords.y + yPos0 - y0);
		color0 = texture(Texture0, scaledTexCorrds);
	}

	float x1 = viewPortParams[1].textureCropParams.x;
	float y1 = viewPortParams[1].textureCropParams.y;
	float wid1 = viewPortParams[1].textureCropParams.z;
	float heig1 = viewPortParams[1].textureCropParams.w;

	float xPos1 = viewPortParams[1].texturePositionParams.x;
	float yPos1 = viewPortParams[1].texturePositionParams.y;
	float widPos1 = viewPortParams[1].texturePositionParams.z;
	float heigPos1 = viewPortParams[1].texturePositionParams.w;
	vec4 color1 = vec4(0.0, 0.0, 0.0, 0.0);


	if((TexCoords.x > x1) && (TexCoords.x < x1 + wid1) && (TexCoords.y > y1) && (TexCoords.y < y1 +  heig1))
	{
		vec2 scaledTexCorrds = vec2(widPos1 * TexCoords.x + xPos1 - x1, heig1 * TexCoords.y + yPos1- y1);
		color1 = texture(Texture0, scaledTexCorrds);
	}

    color = color0 + color1;
}