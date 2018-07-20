
#include "GeometryModel.h"
#include "ResourceManager.h"
#include <glm/gtc/type_ptr.hpp>
#include "GeometryMesh.h"

using namespace FME::Graphics;


GeometryModel::GeometryModel(const std::vector<std::shared_ptr<IMesh>>& meshes, const std::string& shaderNames, GLuint instancing)
{
	m_meshes = meshes;
	m_shaderName = shaderNames;
	m_instancing = instancing;
	m_gameType = RENDER3D;

	m_color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

GeometryModel::GeometryModel(const GeometryType& type, const glm::vec4& color)
{
	m_gameType = RENDER3D;
	std::vector<std::string> textureNames;
	m_color = color;

	if (type == GeometryType::PLANE)
	{
		m_meshes.push_back(GeometryMesh::GeneratePlane(textureNames));
		m_shaderName = "plane";
	}
	else if (type == GeometryType::CUBE)
	{
		m_meshes.push_back(GeometryMesh::GenerateCube(textureNames));
		m_shaderName = "cube";
	}
}

GeometryModel::GeometryModel(const GeometryType& type, const std::string& textureName)
{
	m_gameType = RENDER3D;
	std::vector<std::string> textureNames;
	textureNames.push_back(textureName);
	m_color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

	if (type == GeometryType::PLANE)
	{
		m_meshes.push_back(GeometryMesh::GeneratePlane(textureNames));
		m_shaderName = "plane";
	}
	else if (type == GeometryType::CUBE)
	{
		m_meshes.push_back(GeometryMesh::GenerateCube(textureNames));
		m_shaderName = "cube";
	}
}


void GeometryModel::Draw()
{
	for (int i = 0; i < m_meshes.size(); ++i)
	{
		glUniform4f(glGetUniformLocation(FME::Graphics::ResourceManager::Instance()->GetShader(m_shaderName).GetProgramID(), "userColor"), m_color.x, m_color.y, m_color.z, m_color.w);
		m_meshes[i]->Draw(FME::Graphics::ResourceManager::Instance()->GetShader(m_shaderName).GetProgramID());
	}
}