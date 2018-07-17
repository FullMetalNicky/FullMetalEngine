#include "GameObject.h"
#include "ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine.h"
#include "InputManager.h"

using namespace FME::Graphics;


GameObject::GameObject(std::shared_ptr<IModel> model, const std::string& goName) : IObject()
{
	m_model = model;
	m_name = goName;
}


void GameObject::Draw()
{
	std::string shader = m_model->GetShaderName();
	glm::mat4 view, proj;
	if (RENDER3D == m_model->GetGameType())	Engine::Instance()->GetCamera(view, proj);
	else
	{
		view = glm::mat4(1.0f);
		proj = glm::mat4(1.0f);
	}

	glm::mat4 modelViewProj = proj * view * GetTransformComponent()->GetModelMatrix();

	FME::Graphics::ResourceManager::Instance()->GetShader(shader).Use();
	glUniformMatrix4fv(glGetUniformLocation(FME::Graphics::ResourceManager::Instance()->GetShader(shader).GetProgramID(), "modelViewProj"), 1, GL_FALSE, glm::value_ptr(modelViewProj));
	m_model->Draw();
	FME::Graphics::ResourceManager::Instance()->GetShader(shader).UnUse();
}



void GameObject::Update(double deltaTime)
{
	m_model->Update();
}