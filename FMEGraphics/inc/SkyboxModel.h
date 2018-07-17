#ifndef SKYBOXMODEL_H_
#define SKYBOXMODEL_H_

#include "IModel.h"
#include "OBJMesh.h"


namespace FME
{
	namespace Graphics
	{
		/** \class SkyboxModel
		*  \brief A class for rendering a skybox. Handles the 3D textures and specific rendering definitions. Has a custom shader. 
		*/

		class SkyboxModel : public IModel
		{
		public:

			SkyboxModel(const std::string& textureName);

			virtual void Draw();

		private:
		
		};
	}
}
#endif

