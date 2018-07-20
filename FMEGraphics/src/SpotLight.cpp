#include "SpotLight.h"
#include "ResourceManager.h"

#include <GL/glew.h>

using namespace FME::Graphics;


SpotLight::SpotLight(const std::vector<LightInfo>& lightsInfo)
{
	m_spotLightsInfo = lightsInfo;
}

void SpotLight::Draw()
{
	GLuint programID = ResourceManager::Instance()->GetShader(m_shaderName).GetProgramID();

	for (int i = 0; i < m_spotLightsInfo.size(); ++i)
	{
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("position", i).c_str()), m_spotLightsInfo[i].position.x, m_spotLightsInfo[i].position.y, m_spotLightsInfo[i].position.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("direction", i).c_str()), m_spotLightsInfo[i].direction.x, m_spotLightsInfo[i].direction.y, m_spotLightsInfo[i].direction.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("ambient", i).c_str()),  m_spotLightsInfo[i].ambient.x,  m_spotLightsInfo[i].ambient.y,  m_spotLightsInfo[i].ambient.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("diffuse", i).c_str()),  m_spotLightsInfo[i].diffuse.x,  m_spotLightsInfo[i].diffuse.y,  m_spotLightsInfo[i].diffuse.z);
		glUniform3f(glGetUniformLocation(programID, parseShaderParam("specular", i).c_str()), m_spotLightsInfo[i].specular.x, m_spotLightsInfo[i].specular.y, m_spotLightsInfo[i].specular.z);
		glUniform1f(glGetUniformLocation(programID, parseShaderParam("constant", i).c_str()), m_spotLightsInfo[i].constant);
		glUniform1f(glGetUniformLocation(programID, parseShaderParam("constant", i).c_str()), m_spotLightsInfo[i].linear);
		glUniform1f(glGetUniformLocation(programID, parseShaderParam("constant", i).c_str()), m_spotLightsInfo[i].quadratic);
		glUniform1f(glGetUniformLocation(programID, parseShaderParam("cutOff", i).c_str()), m_spotLightsInfo[i].cutOff);
		glUniform1f(glGetUniformLocation(programID, parseShaderParam("outerCutOff", i).c_str()), m_spotLightsInfo[i].outerCutOff);
	}
	glUniform1i(glGetUniformLocation(programID, "spotLightsNum"), m_spotLightsInfo.size());
}

std::string SpotLight::parseShaderParam(const std::string& paramName, int index)
{
	std::string parsedName = "spotLights.[" + std::to_string(index) + "]" + paramName;

	return parsedName;
}