#ifndef TEXTURE3D_H_
#define TEXTURE3D_H_

#include "ITexture.h"
#include <vector>


namespace FME
{
	namespace Graphics
	{
		/** \class Texture3D
		*  \brief A class handling 3D textures, generating it from memory buffers or using a path to file to read the texture and load it. Use for skybox textures.
		*/

		class Texture3D : public ITexture
		{
		public:
			Texture3D();
			~Texture3D();
			void Generate(GLuint width, GLuint height, const std::vector<std::vector<unsigned char>>& dataVec, bool alpha = false);
			void Generate(const std::vector<std::string>& texturePathVec, bool alpha = false);
			void Update(GLuint width, GLuint height, std::vector<unsigned char*> data, bool alpha = false);

			/*void Update(const std::string& texturePath, bool alpha = false);
			void Update(GLuint width, GLuint height, unsigned char* data, bool alpha = false);*/

			
			void Bind() const;			

		private:

			glm::ivec2 m_texSize; //width, height
			glm::ivec2 m_texFilter; //min, max
			glm::ivec2 m_texWrap; //S, T
			GLuint m_internalFormat; // Format of texture object
			GLuint m_imageFormat; // Format of loaded image		
		};
	}
}
#endif