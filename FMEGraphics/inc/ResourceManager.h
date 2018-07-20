#ifndef RESOURCEMANAGERS_H_
#define RESOURCEMANAGERS_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "ITexture.h"
#include "Shader.h"
#include "IModel.h"
#include <map>
#include <memory>

namespace FME
{
	namespace Graphics
	{
		/** \class ResourceManager
		*  \brief A singleton class that provides the rngine with access to textures and shaders
		*
		*/

		class ResourceManager
		{
		public:

			static std::shared_ptr<ResourceManager> Instance();
			virtual ~ResourceManager();

			Shader   GetShader (std::string name);
			std::shared_ptr<ITexture> GetTexture(std::string name);
			std::shared_ptr<IModel> GetModel(std::string name);

			void LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);

			void LoadModel(const std::shared_ptr<IModel>& model, std::string name);

			void LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
			void LoadTexture(GLuint width, GLuint height, unsigned char* data, bool alpha, std::string name);
			void LoadTexture(const std::vector<std::string>& files, GLboolean alpha, std::string name);	
			void LoadTexture(const std::shared_ptr<ITexture>& texture, std::string name);


		protected:

			ResourceManager();
			static std::shared_ptr<ResourceManager> m_instance;

			std::map<std::string, Shader>    m_shaders;
			std::map<std::string, std::shared_ptr<ITexture>> m_textures;
			std::map<std::string, std::shared_ptr<IModel>>    m_models;
		};
	}
}

#endif