#include "IObject.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace FME::Graphics;

IObject::IObject()
{
	m_components.push_back(std::shared_ptr<TransformComponent>(new TransformComponent));
}

std::shared_ptr<TransformComponent> IObject::GetTransformComponent()
{ 
	for (int i = 0; i < m_components.size(); ++i)
	{
		if ("Transform" == m_components[i]->GetType())
		{

			return std::dynamic_pointer_cast<TransformComponent>(m_components[i]);
		}
	}
};
