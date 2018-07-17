#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D Texture0;
uniform vec4 userColor;

void main()
{    
	vec2 flippedUV = vec2(TexCoords.x, 1.0 - TexCoords.y);
    color = texture(Texture0, flippedUV) * (1.0 - int(0.0 != userColor.w)) + userColor * int(0.0 != userColor.w);
	//color = vec4(0.0, 0.0, 1.0, 1.0);
}