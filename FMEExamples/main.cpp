

#include "Engine.h"


void RenderTextured2DPlane()
{
	FME::Graphics::Engine::Instance()->SetFPS(30.0f);
	FME::Graphics::Engine::Instance()->SetWindowSize(glm::vec2(1280, 720));
	FME::Graphics::Engine::Instance()->SetScene("Textured2DPlane.json");

	double deltaTime = 0.0;
	double lastFrame = 0.0;
	
	while (FME::Graphics::Engine::Instance()->Alive())
	{
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		FME::Graphics::Engine::Instance()->Update(deltaTime);
		FME::Graphics::Engine::Instance()->Draw();
	}
}




int main()
{
	RenderTextured2DPlane();

	return 0;
}