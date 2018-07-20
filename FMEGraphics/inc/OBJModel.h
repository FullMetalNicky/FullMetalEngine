#ifndef OBJMODEL_H_
#define OBJMODEL_H_

#include "IModel.h"
#include "OBJMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace FME
{
	namespace Graphics
	{
		/** \class OBJModel
		*  \brief A class implementing OBJ models as loaded using ASSIMP. Has a special shader for rendering ASSIMP OBJs.
		* I used the tutorial at LearnOprnGL website for writing specific parts of this class. 
		*/

		class OBJModel : public IModel
		{
		public:

			OBJModel(const std::string& objPath);

			virtual void Draw();

		private:

			void loadModel(const std::string& objPath);
			void processNode(aiNode *node, const aiScene *scene);
			std::shared_ptr<OBJMesh> processMesh(aiMesh *mesh, const aiScene *scene);

			std::vector<std::string> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
			std::vector<std::string> m_textureNamesLoaded;
			std::string m_directory;			
		};
	}
}
#endif

