#include "NoEffect.h"
#include <iostream>
#include "ResourceManager.h"


using namespace FME::Graphics;


NoEffect::NoEffect(glm::ivec2 screenSize) : IEffect()
{
	m_screenShaderName = "NoEffect";
	ResourceManager::Instance()->LoadShader("../FMEGraphics/shaders/NoEffect.vert", "../FMEGraphics/shaders/NoEffect.frag", nullptr, m_screenShaderName);

	// framebuffer configuration	
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	ResourceManager::Instance()->LoadTexture(GLuint(screenSize.x), GLuint(screenSize.y), nullptr, true, std::string("NoEffect"));
	std::shared_ptr<ITexture> texture = ResourceManager::Instance()->GetTexture(std::string("NoEffect"));
	texture->SetName(std::string("NoEffect"));
	texture->Bind();

	m_outputTextureNames.push_back(texture->GetName());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetTextureID(), 0); 
	m_renderQuad = FME::Graphics::GeometryMesh::GeneratePlane(m_outputTextureNames);

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &m_renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenSize.x, screenSize.y); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer); // now actually attach it

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

NoEffect::~NoEffect()
{
	glDeleteFramebuffers(1, &m_frameBuffer);
	glDeleteRenderbuffers(1, &m_renderBuffer);
}


void NoEffect::RenderStart()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)							
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NoEffect::RenderEnd()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void NoEffect::RenderToScreen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.						
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	ResourceManager::Instance()->GetShader(m_screenShaderName).Use();
	m_renderQuad->Draw(ResourceManager::Instance()->GetShader(m_screenShaderName).GetProgramID());
	ResourceManager::Instance()->GetShader(m_screenShaderName).UnUse();
}