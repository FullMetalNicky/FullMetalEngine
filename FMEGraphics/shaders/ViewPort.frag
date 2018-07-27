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
	color = vec4(0.0, 0.0, 0.0, 1.0);

	if((TexCoords.x > viewPortParams[0].texturePositionParams.x) && (TexCoords.y > viewPortParams[0].texturePositionParams.y) && (TexCoords.y < viewPortParams[0].texturePositionParams.y + viewPortParams[0].texturePositionParams.w) && (TexCoords.x < viewPortParams[0].texturePositionParams.x + viewPortParams[0].texturePositionParams.z))
	{
		vec2 scaledTexCoords = vec2(TexCoords.x  - viewPortParams[0].texturePositionParams.x + viewPortParams[0].textureCropParams.x, TexCoords.y  - viewPortParams[0].texturePositionParams.y + viewPortParams[0].textureCropParams.y);
		color += texture(Texture0, scaledTexCoords);
	}

	if((TexCoords.x > viewPortParams[1].texturePositionParams.x) && (TexCoords.y > viewPortParams[1].texturePositionParams.y) && (TexCoords.y < viewPortParams[1].texturePositionParams.y + viewPortParams[1].texturePositionParams.w) && (TexCoords.x < viewPortParams[1].texturePositionParams.x + viewPortParams[1].texturePositionParams.z))
	{
		vec2 scaledTexCoords = vec2(TexCoords.x  - viewPortParams[1].texturePositionParams.x + viewPortParams[1].textureCropParams.x, TexCoords.y  - viewPortParams[1].texturePositionParams.y + viewPortParams[1].textureCropParams.y);
		color += texture(Texture1, scaledTexCoords);
	}
}