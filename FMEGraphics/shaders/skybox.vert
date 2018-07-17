#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 TexCoords;
out vec3 Normal;
uniform mat4 modelViewProj;

void main()
{
    gl_Position = modelViewProj * vec4(position, 1.0f);	
	TexCoords = position;
	Normal = normal;
}
