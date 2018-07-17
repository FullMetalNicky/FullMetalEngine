#ifndef OBJMESH_H_
#define OBJMESH_H_

#include "IMesh.h"
#include "Texture2D.h"


namespace FME
{
	namespace Graphics
	{
		/** \class OBJMesh
		*  \brief A class for containing OBJ meshes as loaded using ASSIMP. Handles different texture types.
		*/

		class OBJMesh : public IMesh
		{
		public:

			OBJMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::string>& textureNames);

			virtual void Draw(GLuint m_programID);
		};

	}
}
#endif