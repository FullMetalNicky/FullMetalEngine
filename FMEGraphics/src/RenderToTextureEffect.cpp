#include "RenderToTextureEffect.h"
#include <iostream>
#include "ResourceManager.h"


using namespace FME::Graphics;


RenderToTextureEffect::RenderToTextureEffect(glm::ivec2 screenSize, const std::string& textureNameByUser) : IEffect()
{
	m_screenShaderName = "RenderToTextureEffect";
	std::string textureName;
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	if ("" == textureNameByUser) textureName = "RenderToTextureEffect";
	else textureName = textureNameByUser;

	ResourceManager::Instance()->LoadTexture(GLuint(screenSize.x), GLuint(screenSize.y), nullptr, true, textureName);
	std::shared_ptr<ITexture> texture = ResourceManager::Instance()->GetTexture(textureName);
	texture->SetName(textureName);
	texture->Bind();

	m_outputTextureNames.push_back(texture->GetName());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetTextureID(), 0); 
	m_renderQuad = FME::Graphics::GeometryMesh::GeneratePlane(m_outputTextureNames);

	glGenRenderbuffers(1, &m_renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenSize.x, screenSize.y); 
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer); 

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

RenderToTextureEffect::~RenderToTextureEffect()
{
	glDeleteFramebuffers(1, &m_frameBuffer);
	glDeleteRenderbuffers(1, &m_renderBuffer);
}


void RenderToTextureEffect::RenderStart()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glEnable(GL_DEPTH_TEST); 					
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderToTextureEffect::RenderEnd()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void RenderToTextureEffect::RenderToScreen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); 						
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);

	ResourceManager::Instance()->GetShader(m_screenShaderName).Use();
	m_renderQuad->Draw(ResourceManager::Instance()->GetShader(m_screenShaderName).GetProgramID());
	ResourceManager::Instance()->GetShader(m_screenShaderName).UnUse();
}