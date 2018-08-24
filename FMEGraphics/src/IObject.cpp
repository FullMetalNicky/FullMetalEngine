#include "IObject.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace FME::Graphics;

IObject::IObject()
{
	m_components.push_back(std::shared_ptr<TransformComponent>(new TransformComponent));
}



void IObject::AddComponent(std::shared_ptr<IComponent> component)
{
	m_components.push_back(component);
}


std::shared_ptr<IComponent> IObject::GetComponentByType(const std::string& type)
{
	for (int i = 0; i < m_components.size(); ++i)
	{
		if (type == m_components[i]->GetType())
		{
			return m_components[i];
		}
	}
	return nullptr;
}

