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
	if(TexCoords.x < 0.7) color = texture(Texture0, vec2(TexCoords.x / 0.7, TexCoords.y));
	else 
	{
		vec2 scaledTexCoords = vec2(- 0.35 + TexCoords.x, TexCoords.y);
		color = texture(Texture1, scaledTexCoords);
	}
	//color = texture(Texture1, TexCoords);
}