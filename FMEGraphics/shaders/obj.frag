#version 330 core

in vec3 pos;
in vec2 TexCoords;
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;

//light related

in vec3 FragPos;
in vec3 Normal;
out vec4 color;

#define MAX_LIGHTS 4

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLights[MAX_LIGHTS];
uniform vec3 viewPos;
uniform int dirLightsNum;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse0, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse0, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular0, TexCoords));
    return (ambient + diffuse + specular);
}

void main()
{    
	vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < dirLightsNum; i++)
	{
        result += CalcDirLight(dirLights[i], norm, viewDir);
	}

	color = vec4(result , 1.0);
}