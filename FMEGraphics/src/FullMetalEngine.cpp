#include "FullMetalEngine.h"
#include "Engine.h"

using namespace FME::Graphics;


bool FullMetalEngine::Alive()
{
	return Engine::Instance()->Alive();
}


void FullMetalEngine::Update(double deltaTime)
{
	Engine::Instance()->Update(deltaTime);
}


void FullMetalEngine::Draw()
{
	Engine::Instance()->Draw();
}


void FullMetalEngine::SetWindowSize(int windowWidth, int windowHeight)
{
	Engine::Instance()->SetWindowSize(glm::ivec2(windowWidth, windowHeight));
}


void FullMetalEngine::SetScene(const std::string& jsonPath)
{
	Engine::Instance()->SetScene(jsonPath);
}

void FullMetalEngine::SetEffects(const std::string& jsonPath)
{
	Engine::Instance()->SetEffects(jsonPath);
}


void FullMetalEngine::SetFPS(double fps)
{
	Engine::Instance()->SetFPS(fps);
}