#include "Pipeline.h"
#include "BloomEffect.h"
#include "RenderToTextureEffect.h"
#include "ViewPortEffect.h"
#include "Engine.h"

using namespace FME::Graphics;


Pipeline::Pipeline(const glm::ivec2 & windowSize)
{
	m_windowSize = windowSize;
}

Pipeline::~Pipeline()
{

}

void Pipeline::AddEffect(EffectParams effect)
{
	if (effect.type == "RenderToTextureEffect")
	{
		effect.effect = std::shared_ptr<RenderToTextureEffect>(new RenderToTextureEffect(m_windowSize, effect.Id));
	}
	else if (effect.type == "BloomEffect")
	{
		effect.effect = std::shared_ptr<BloomEffect>(new BloomEffect(m_windowSize));
	}
	else if (effect.type == "ViewPortEffect")
	{
		/*"TextureParams": [
          {
            "Name": "RenderToTextureEffect1",
            "textureCropParams": {
              "x": "0.15",
              "y": "0.0",
              "w": "0.7",
              "h": "1.0"
            },
            "textureScreenParams": {
              "x": "0.0",
              "y": "0.0",
              "w": "0.7",
              "h": "1.0"
            }
          },
          {
            "Name": "RenderToTextureEffect2",
            "textureCropParams": {
              "x": "0.35",
              "y": "0.0",
              "w": "0.3",
              "h": "1.0"
            },
            "textureScreenParams": {
              "x": "0.7",
              "y": "0.0",
              "w": "0.3",
              "h": "1.0"
            }
          }
        ]*/
		std::vector<ViewPortParams> params = { ViewPortParams{ "RenderToTextureEffect1",
			glm::vec4(0.15, 0.0, 0.7, 1.0),
			glm::vec4(0.0, 0.0, 0.7, 1.0) },
			ViewPortParams{ "RenderToTextureEffect2",
			glm::vec4(0.35, 0.0, 0.3, 1.0),
			glm::vec4(0.7, 0.0, 0.3, 1.0) } };
		effect.effect = std::shared_ptr<ViewPortEffect>(new ViewPortEffect(m_windowSize, params));
	}

	m_effects.push_back(effect);
}


void Pipeline::Update()
{

}



void Pipeline::ClearScreen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Pipeline::Render(const std::shared_ptr<SceneObject>& scene)
{
	ClearScreen();
	int activeCamera = Engine::Instance()->GetActiveCamera();
	for (int i = 0; i < m_effects.size(); ++i)
	{
		if (-1 != m_effects[i].activeCamera) Engine::Instance()->SetActiveCamera(m_effects[i].activeCamera);
		else Engine::Instance()->SetActiveCamera(activeCamera);

		if (m_effects[i].draw)
		{
			m_effects[i].effect->RenderStart();
			scene->Draw();
			m_effects[i].effect->RenderEnd();
		}
	}
	if (m_effects.size())
	{
		m_effects[m_effects.size() - 1].effect->RenderToScreen();
	}
	else
	{
		scene->Draw();
	}
	Engine::Instance()->SetActiveCamera(activeCamera);
}