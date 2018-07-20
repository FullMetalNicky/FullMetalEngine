#version 330 core

in vec3 pos;
in vec2 TexCoords;
out vec4 color;


uniform sampler2D Texture0;

void main()
{    
   	color = vec4(pos , 1.0) + vec4(0.5, 0.5, 0.5, 0.0);
}