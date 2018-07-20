#ifndef IMESH_H_
#define IMESH_H_

#include "ITexture.h"
#include <vector>
#include <memory>


namespace FME
{
	namespace Graphics
	{
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
		};

		/** \class IMesh
		*  \brief An interface class for all drawable objects - containing vertex information and textures. 
		*/

		class IMesh
		{
		public:

			virtual ~IMesh();

			IMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::string>& textureNames);

			virtual void Draw(GLuint m_programID);
			
			static void FloatsToVertices(const std::vector<float>& floats, std::vector<Vertex>& vertices);
			virtual void SetName(const std::string& name) { m_name = name; };
			std::string GetName() const { return m_name; };

		protected:

			void initMesh();

			std::vector<Vertex> m_vertices;
			std::vector<unsigned int> m_indices;
			std::vector<std::string> m_textureNames;

			std::string m_name;

			GLuint m_VBO;
			GLuint m_VAO;
			GLuint m_EBO;
		};

	}
}
#endif
