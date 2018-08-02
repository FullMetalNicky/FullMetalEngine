#ifndef GEOMETRYMODEL_H_
#define GEOMETRYMODEL_H_

#include "IModel.h"


namespace FME
{
	namespace Graphics
	{
		/** \class GeometryModel
		*  \brief A  class that implements a geometric model. Can contain several meshes, all rendered using the same shader given as input.
		*/

		enum GeometryType
		{
			PLANE,
			CUBE,
			CYLINDER
		};

		class GeometryModel : public IModel
		{
			public:

			GeometryModel(const std::vector<std::shared_ptr<IMesh>>& meshes, const std::string& shaderName, GLuint instancing = 0);
			
			GeometryModel(const GeometryType& type, const std::string& textureName);

			GeometryModel(const GeometryType& type, const glm::vec4& color);

			void Draw();

			private:
			
				glm::vec4 m_color;
		};
	}
}

#endif