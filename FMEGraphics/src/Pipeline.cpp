#include "Pipeline.h"

using namespace FME::Graphics;


Pipeline::Pipeline()
{

}

Pipeline::~Pipeline()
{

}

void Pipeline::AddEffect(std::shared_ptr<IEffect> effect, const std::string& effectName)
{
	m_effects[effectName] = effect;
}

void Pipeline::Update()
{

}


void Pipeline::RenderStart(const std::string& currentEffectName)
{
	m_currentEffect = currentEffectName;
	m_effects[m_currentEffect]->RenderStart();
}


void Pipeline::RenderEnd()
{
	m_effects[m_currentEffect]->RenderEnd();
}


void Pipeline::ClearScreen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Pipeline::RenderToScreen()
{
	m_effects[m_currentEffect]->RenderToScreen();
}