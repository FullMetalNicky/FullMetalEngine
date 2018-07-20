
#include "OBJMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ResourceManager.h"

using namespace FME::Graphics;



OBJMesh::OBJMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::string>& textureNames) : IMesh(vertices, indices, textureNames)
{

}


void OBJMesh::Draw(GLuint m_programID)
{
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;
	for(unsigned int i = 0; i < m_textureNames.size(); i++)
	{
		std::shared_ptr<ITexture> t = ResourceManager::Instance()->GetTexture(m_textureNames[i]);
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = t->GetType();
		std::string texName;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
			texName = name + number;
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++);
			texName = name + number;
		}

	//	shader.setFloat(("material." + name + number).c_str(), i);
		glUniform1i(glGetUniformLocation(m_programID, texName.c_str()), i);
		t->Bind();
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}