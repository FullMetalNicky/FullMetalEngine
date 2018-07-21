#include "BloomEffect.h"
#include <iostream>
#include "ResourceManager.h"
#include "Engine.h"

using namespace FME::Graphics;


BloomEffect::BloomEffect(glm::ivec2 screenSize) : IEffect()
{
	m_screenShaderName = "RenderToTextureEffect";
	m_bloomEffectShader = "BloomEffect";
	m_guassianShader = "guassian";
	m_HPFShader = "HPF";

	m_windowSize = screenSize;
	std::vector<std::string> texVec;
	m_renderQuad = FME::Graphics::GeometryMesh::GeneratePlane(texVec);

	glGenFramebuffers(1, &m_hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_hdrFBO);

	std::shared_ptr<Texture2D> renderSceneTexture(new Texture2D);
	renderSceneTexture->Generate(m_windowSize, glm::ivec2(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE), GL_RGB16F, GL_RGB, GL_FLOAT , nullptr);
	renderSceneTexture->SetName("renderSceneTexture");
	renderSceneTexture->Bind();	
	m_textures["renderSceneTexture"] = renderSceneTexture;
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderSceneTexture->GetTextureID(), 0);

	glGenRenderbuffers(1, &m_rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_windowSize.x, m_windowSize.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rboDepth);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenFramebuffers(1, &m_hdrFBOAfterHPF);
	glBindFramebuffer(GL_FRAMEBUFFER, m_hdrFBOAfterHPF);

	std::shared_ptr<Texture2D> HPFTexture(new Texture2D);
	HPFTexture->Generate(m_windowSize, glm::ivec2(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE), GL_RGB16F, GL_RGB, GL_FLOAT, nullptr);
	HPFTexture->SetName("HPFTexture");
	HPFTexture->Bind();
	m_textures["HPFTexture"] = HPFTexture;
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, HPFTexture->GetTextureID(), 0);
	
	glGenRenderbuffers(1, &m_rboDepthAfterHPF);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboDepthAfterHPF);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_windowSize.x, m_windowSize.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rboDepthAfterHPF);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glGenFramebuffers(2, m_pingpongFBO);

	std::shared_ptr<Texture2D> gaussianTextures[2] {
		std::shared_ptr<Texture2D>(new Texture2D),
		std::shared_ptr<Texture2D>(new Texture2D)
	};

	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_pingpongFBO[i]);
		gaussianTextures[i]->Generate(m_windowSize, glm::ivec2(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE), GL_RGB16F, GL_RGB, GL_FLOAT, nullptr);
		gaussianTextures[i]->SetName("gaussianTextures" + std::to_string(i));
		gaussianTextures[i]->Bind();
		m_textures["gaussianTextures" + std::to_string(i)] = gaussianTextures[i];
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gaussianTextures[i]->GetTextureID(), 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}
}

BloomEffect::~BloomEffect()
{
	glDeleteFramebuffers(1, &m_hdrFBO);
	glDeleteRenderbuffers(1, &m_rboDepth);
	glDeleteFramebuffers(1, &m_hdrFBOAfterHPF);
	glDeleteRenderbuffers(1, &m_rboDepthAfterHPF);
	glDeleteFramebuffers(2, m_pingpongFBO);	
}


void BloomEffect::RenderStart()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_hdrFBO);
	glEnable(GL_DEPTH_TEST); 							
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BloomEffect::RenderEnd()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_hdrFBOAfterHPF);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST); 				
	glDisable(GL_BLEND);

	ResourceManager::Instance()->GetShader(m_HPFShader).Use();
	glBindTexture(GL_TEXTURE_2D, m_textures["renderSceneTexture"]->GetTextureID());
	m_renderQuad->Draw(ResourceManager::Instance()->GetShader(m_HPFShader).GetProgramID());
	ResourceManager::Instance()->GetShader(m_HPFShader).UnUse();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	bool horizontal = true, first_iteration = true;
	unsigned int amount = 10;
	ResourceManager::Instance()->GetShader(m_guassianShader).Use();

	for (unsigned int i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_pingpongFBO[horizontal]);

		glUniform1i(glGetUniformLocation(ResourceManager::Instance()->GetShader(m_guassianShader).GetProgramID(), "horizontal"), horizontal);
		glBindTexture(GL_TEXTURE_2D, first_iteration ? m_textures["HPFTexture"]->GetTextureID() : m_textures["gaussianTextures" + std::to_string(!horizontal)]->GetTextureID());

		m_renderQuad->Draw(ResourceManager::Instance()->GetShader(m_guassianShader).GetProgramID());

		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}
	ResourceManager::Instance()->GetShader(m_guassianShader).UnUse();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void BloomEffect::RenderToScreen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); 			
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);

	ResourceManager::Instance()->GetShader(m_bloomEffectShader).Use();
	glUniform1i(glGetUniformLocation(ResourceManager::Instance()->GetShader(m_bloomEffectShader).GetProgramID(), "texture0"), 0);
	glUniform1i(glGetUniformLocation(ResourceManager::Instance()->GetShader(m_bloomEffectShader).GetProgramID(), "texture1"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textures["renderSceneTexture"]->GetTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_textures["gaussianTextures" + std::to_string(0)]->GetTextureID());

	m_renderQuad->Draw(ResourceManager::Instance()->GetShader(m_bloomEffectShader).GetProgramID());
	ResourceManager::Instance()->GetShader(m_bloomEffectShader).UnUse();
}