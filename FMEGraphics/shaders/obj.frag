#version 330 core

in vec3 pos;
in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;

void main()
{    
    color = texture(texture_diffuse0, TexCoords);
	//color = vec4(1.0, 0.0, 0.0 , 1.0);
}