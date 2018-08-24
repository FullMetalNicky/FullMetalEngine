#include "RenderComponent.h"

using namespace FME::Graphics;


RenderComponent::RenderComponent(std::shared_ptr<IModel> model)
{
	m_type = "Render";
	m_model = model;
}



void RenderComponent::Update()
{
	m_model->Update();
}


void RenderComponent::Draw()
{
	m_model->Draw();
}


std::string RenderComponent::GetShaderName() const
{
	return m_model->GetShaderName();
}