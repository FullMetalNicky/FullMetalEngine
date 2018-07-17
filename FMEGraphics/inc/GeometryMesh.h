#ifndef GEOMETRYMESH_H_
#define GEOMETRYMESH_H_

#include "IMesh.h"
#include "Texture2D.h"
#include <memory>

namespace FME
{
	namespace Graphics
	{
		/** \class GeometryMesh
		*  \brief A  class that implements a geometric shape. Shapes can be generates through pre-defined geomtery like planes or cubes, or by using 
		* a parametric representation of a surface
		*/

		class GeometryMesh : public IMesh
		{
		public:
			GeometryMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::string>& textureNames);

			static std::shared_ptr<GeometryMesh> GeneratePlane(const std::vector<std::string>& textureNames); // on the X-Y plane
			static std::shared_ptr<GeometryMesh> GenerateCube(const std::vector<std::string>& textureNames);
			static std::shared_ptr<GeometryMesh> GenerateMesh(glm::ivec3 gridDim, glm::vec3(*func)(glm::vec3, glm::vec3), const std::vector<std::string>& textureNames);

			virtual ~GeometryMesh();

		};

	}
}

#endif
