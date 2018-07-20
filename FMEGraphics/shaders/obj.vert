#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 pos;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 modelViewProj;

//light related
uniform mat4 transInvModel;
uniform mat4 model;

void main()
{
    gl_Position = modelViewProj * vec4(position, 1.0f);
	pos = position;
	TexCoords = texCoords;
	gl_PointSize = 4.0;

	Normal = mat3(transInvModel) * normal;  
	FragPos = vec3(model * vec4(position, 1.0));
}
