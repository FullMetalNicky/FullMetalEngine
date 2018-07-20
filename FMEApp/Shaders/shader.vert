#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;
out vec3 pos;
uniform mat4 modelViewProj;

void main()
{
    gl_Position = modelViewProj * vec4(position, 1.0f);
	pos = position;
	TexCoords = texCoords;
	gl_PointSize = 4.0;
}
