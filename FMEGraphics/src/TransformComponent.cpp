#include "TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>


using namespace FME::Graphics;


TransformComponent::TransformComponent()
{
	m_type = "Transform";
	m_translation = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
}


void TransformComponent::ResetTransform()
{
	m_fixedTransform = false;
	m_transform = Transform{ m_translation, m_rotation, m_scale };
}

void TransformComponent::Update()
{
	if (!m_fixedTransform) m_transform = Transform{ m_translation, m_rotation, m_scale };
}

glm::mat4 TransformComponent::GetModelMatrix() const
{	
	glm::mat4 model;
	glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(m_transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(m_transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rot = rotX * rotY * rotZ;
	glm::mat4 scale;

	if (nullptr == m_parent)
	{
		scale = glm::scale(glm::mat4(1.0f), m_transform.Scale);
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_transform.Translation);
		model = trans * rot * scale * glm::mat4(1.0f);
	}
	else
	{
		glm::mat4 parentRotX = glm::rotate(glm::mat4(1.0f), glm::radians(m_parent->GetTransform().Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 parentRotY = glm::rotate(glm::mat4(1.0f), glm::radians(m_parent->GetTransform().Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 parentRotZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_parent->GetTransform().Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 parentRot = parentRotX * parentRotY * parentRotZ;

		glm::mat4 worldRotX = glm::rotate(glm::mat4(1.0f), glm::radians(m_parent->GetTransform().Rotation.x + m_transform.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 worldRotY = glm::rotate(glm::mat4(1.0f), glm::radians(m_parent->GetTransform().Rotation.y + m_transform.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 worldRotZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_parent->GetTransform().Rotation.z + m_transform.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 worldRot = worldRotX * worldRotY * worldRotZ;

		glm::vec3 transLocalVec = (m_parent->GetTransform().Scale * m_transform.Translation);
		glm::mat4 transLocalMat = glm::translate(glm::mat4(1.0f), transLocalVec);
		glm::mat4 trans = glm::translate(parentRot * transLocalMat, m_parent->GetTransform().Translation);		

		scale = glm::scale(glm::mat4(1.0f), m_transform.Scale * m_parent->GetTransform().Scale);

		model = trans * rot * scale * glm::mat4(1.0f);
	}

	return model;
}



void TransformComponent::SetTransform(const Transform& transform)
{
	m_translation = transform.Translation;
	m_rotation = transform.Rotation;
	m_scale = transform.Scale;
	m_transform = Transform{ m_translation, m_rotation, m_scale };
}

void TransformComponent::SetFixedTransform(const Transform& transform)
{
	m_fixedTransform = true;
	m_transform = transform;
}