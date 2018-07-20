#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;

void main()
{    
    color = texture(ourTexture, TexCoords);
	//color = vec4(0.0, 0.0, 1.0, 1.0);
}