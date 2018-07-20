#include "DirectionalLight.h"
#include "ResourceManager.h"

#include <GL/glew.h>

using namespace FME::Graphics;


DirectionalLight::DirectionalLight(const std::string& shaderName, const std::vector<DirLightInfo>& lightsInfo) : LightObject(shaderName)
{
	m_dirLightsInfo = lightsInfo;
}

void DirectionalLight::Draw()
{
	GLuint programID = ResourceManager::Instance()->GetShader(m_shaderName).GetProgramID();

	for (int i = 0; i < m_dirLightsInfo.size(); ++i)
	{
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("direction", i).c_str()), m_dirLightsInfo[i].direction.x, m_dirLightsInfo[i].direction.y, m_dirLightsInfo[i].direction.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("ambient", i).c_str()), m_dirLightsInfo[i].ambient.x, m_dirLightsInfo[i].ambient.y, m_dirLightsInfo[i].ambient.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("diffuse", i).c_str()), m_dirLightsInfo[i].diffuse.x, m_dirLightsInfo[i].diffuse.y, m_dirLightsInfo[i].diffuse.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("specular", i).c_str()), m_dirLightsInfo[i].specular.x, m_dirLightsInfo[i].specular.y, m_dirLightsInfo[i].specular.z);
	}
	glUniform1i(glGetUniformLocation(programID, "dirLightsNum"), m_dirLightsInfo.size());
}

std::string DirectionalLight::parseShaderParam(const std::string& paramName, int index)
{
	std::string parsedName = "dirLights.[" + std::to_string(index) + "]" + paramName;

	return parsedName;
}