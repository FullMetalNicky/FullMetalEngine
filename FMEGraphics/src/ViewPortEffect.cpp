#include "ViewPortEffect.h"
#include "ResourceManager.h"

using namespace FME::Graphics;


ViewPortEffect::ViewPortEffect(glm::ivec2 screenSize, const std::vector<ViewPortParams>& viewPortParams) : IEffect()
{
	m_screenShaderName = "ViewPort";
	m_viewPortParams = viewPortParams;
	for (int i = 0; i < m_viewPortParams.size(); ++i)
	{
		m_outputTextureNames.push_back(m_viewPortParams[i].textureName);
	}

	m_renderQuad = FME::Graphics::GeometryMesh::GeneratePlane(m_outputTextureNames);
}


ViewPortEffect::~ViewPortEffect()
{

}


void ViewPortEffect::RenderStart()
{

}


void ViewPortEffect::RenderEnd()
{

}


void ViewPortEffect::RenderToScreen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	GLuint programID = ResourceManager::Instance()->GetShader(m_screenShaderName).GetProgramID();

	ResourceManager::Instance()->GetShader(m_screenShaderName).Use();
	for (int i = 0; i < m_viewPortParams.size(); ++i)
	{
		glUniform4f(glGetUniformLocation(programID, parseShaderParam("textureCropParams", i).c_str()), m_viewPortParams[i].textureCropParams.x, m_viewPortParams[i].textureCropParams.y, m_viewPortParams[i].textureCropParams.z, m_viewPortParams[i].textureCropParams.w);
		glUniform4f(glGetUniformLocation(programID, parseShaderParam("texturePositionParams", i).c_str()), m_viewPortParams[i].texturePositionParams.x, m_viewPortParams[i].texturePositionParams.y, m_viewPortParams[i].texturePositionParams.z, m_viewPortParams[i].texturePositionParams.w);
	}
	glUniform1i(glGetUniformLocation(programID, "viewPortParamsNum"), m_viewPortParams.size());


	m_renderQuad->Draw(ResourceManager::Instance()->GetShader(m_screenShaderName).GetProgramID());
	ResourceManager::Instance()->GetShader(m_screenShaderName).UnUse();
}

std::string ViewPortEffect::parseShaderParam(const std::string& paramName, int index)
{
	std::string parsedName = "viewPortParams[" + std::to_string(index) + "]." + paramName;

	return parsedName;
}