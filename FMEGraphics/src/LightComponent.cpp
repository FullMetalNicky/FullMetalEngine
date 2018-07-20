#include "LightComponent.h"
#include "ResourceManager.h"

using namespace FME::Graphics;



LightComponent::LightComponent(const std::vector<std::shared_ptr<LightObject>>& lights)
{
	m_type = "Light";
	m_lights = lights;
}


void LightComponent::Draw()
{
	for (int i = 0; i < m_lights.size(); ++i)
	{
		m_lights[i]->Draw();
	}
}