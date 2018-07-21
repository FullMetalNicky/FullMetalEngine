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

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

uniform DirLight dirLights[MAX_LIGHTS];
uniform SpotLight spotLights[MAX_LIGHTS];
uniform PointLight pointLights[MAX_LIGHTS];


uniform int dirLightsNum;
uniform int spotLightsNum;
uniform int pointLightsNum;

uniform vec3 viewPos;


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

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse0, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse0, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular0, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse0, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse0, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular0, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
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
	for(int i = 0; i < pointLightsNum; i++)
	{
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}
	for(int i = 0; i < spotLightsNum; i++)
	{
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
	}

	color = int(0 == dirLightsNum) * texture(texture_diffuse0, TexCoords) + int(0 < dirLightsNum) * vec4(result , 1.0);
}