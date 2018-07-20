#include "SkyboxModel.h"
#include "GeometryMesh.h"
#include "Texture3D.h"
#include "ResourceManager.h"
#include <glm/gtc/type_ptr.hpp>

using namespace FME::Graphics;




SkyboxModel::SkyboxModel(const std::string& textureName)
{
	m_shaderName = "skybox";
	ResourceManager::Instance()->LoadShader("../FMEGraphics/shaders/skybox.vert", "../FMEGraphics/shaders/skybox.frag", nullptr, m_shaderName);

	std::vector<std::string> textureNames;
	textureNames.push_back(textureName);

	m_meshes.push_back(GeometryMesh::GenerateCube(textureNames));
	m_gameType = RENDER3D;
}


void SkyboxModel::Draw()
{
	glDepthMask(GL_FALSE);

	for (int i = 0; i < m_meshes.size(); ++i)
	{		
		m_meshes[i]->Draw(FME::Graphics::ResourceManager::Instance()->GetShader(m_shaderName).GetProgramID());
	}
	glDepthMask(GL_TRUE);
}
