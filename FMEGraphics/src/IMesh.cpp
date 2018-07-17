#include "IMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ResourceManager.h"

using namespace FME::Graphics;

/*
IMesh::IMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<ITexture>>& textures)
{
	m_vertices = vertices;
	m_indices = indices;
	m_textures = textures;	

	initMesh();
}*/

IMesh::IMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::string>& textureNames)
{
	m_vertices = vertices;
	m_indices = indices;
	m_textureNames = textureNames;

	initMesh();
}


IMesh::~IMesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}


void IMesh::initMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void IMesh::FloatsToVertices(const std::vector<float>& floats, std::vector<Vertex>& vertices)
{
	for (int i = 0; i < floats.size(); i += 8)
	{
		Vertex v;
		v.Position = glm::vec3(floats[i], floats[i + 1], floats[i + 2]);
		v.Normal = glm::vec3(floats[i + 3], floats[i + 4], floats[i + 5]);
		v.TexCoords = glm::vec2(floats[i + 6], floats[i + 7]);
		vertices.push_back(v);
	}
}


void IMesh::Draw(GLuint m_programID)
{	
	for (unsigned int i = 0; i < m_textureNames.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		ResourceManager::Instance()->GetTexture(m_textureNames[i])->Bind();
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
