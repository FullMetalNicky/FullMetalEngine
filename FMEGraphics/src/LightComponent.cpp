#include "LightComponent.h"
#include "ResourceManager.h"
#include "Engine.h"

using namespace FME::Graphics;



LightComponent::LightComponent(const std::vector<std::shared_ptr<LightObject>>& lights)
{
	m_type = "Light";
	m_lights = lights;
}


void LightComponent::Draw()
{
	glm::vec3 viewPos = Engine::Instance()->GetCameraPosition();
	GLuint programID = ResourceManager::Instance()->GetShader(m_shaderName).GetProgramID();
	glUniform3f(glGetUniformLocation(programID, "viewPos"), viewPos.x, viewPos.y, viewPos.z);

	for (int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->Draw();
	}
}

void LightComponent::SetShader(const std::string& shaderName)
{
	m_shaderName = shaderName;

	for (int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->SetShader(shaderName);
	}
}