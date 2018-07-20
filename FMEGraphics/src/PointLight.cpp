#include "PointLight.h"
#include "ResourceManager.h"

#include <GL/glew.h>

using namespace FME::Graphics;


PointLight::PointLight(const std::vector<LightInfo>& lightsInfo)
{
	m_pointLightsInfo = lightsInfo;
}

void PointLight::Draw()
{
	GLuint programID = ResourceManager::Instance()->GetShader(m_shaderName).GetProgramID();

	for (int i = 0; i < m_pointLightsInfo.size(); ++i)
	{
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("position", i).c_str()), m_pointLightsInfo[i].position.x, m_pointLightsInfo[i].position.y, m_pointLightsInfo[i].position.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("ambient", i).c_str()),   m_pointLightsInfo[i].ambient.x,   m_pointLightsInfo[i].ambient.y,   m_pointLightsInfo[i].ambient.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("diffuse", i).c_str()),   m_pointLightsInfo[i].diffuse.x,   m_pointLightsInfo[i].diffuse.y,   m_pointLightsInfo[i].diffuse.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("specular", i).c_str()),  m_pointLightsInfo[i].specular.x,  m_pointLightsInfo[i].specular.y,  m_pointLightsInfo[i].specular.z);
		glUniform1f(glGetUniformLocation(programID, parseShaderParam("constant", i).c_str()), m_pointLightsInfo[i].constant);
		glUniform1f(glGetUniformLocation(programID, parseShaderParam("constant", i).c_str()), m_pointLightsInfo[i].linear);
		glUniform1f(glGetUniformLocation(programID, parseShaderParam("constant", i).c_str()), m_pointLightsInfo[i].quadratic);

	}
	glUniform1i(glGetUniformLocation(programID, "pointLightsNum"), m_pointLightsInfo.size());
}

std::string PointLight::parseShaderParam(const std::string& paramName, int index)
{
	std::string parsedName = "pointLights.[" + std::to_string(index) + "]" + paramName;

	return parsedName;
}