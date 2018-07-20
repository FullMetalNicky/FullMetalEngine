#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "ITexture.h"

namespace FME
{
	namespace Graphics
	{
		/** \class Texture2D
		*  \brief A class handling 2D textures, generating it from memory buffers or using a path to file to read the texture and load it. 
		*/

		class Texture2D : public ITexture
		{
		public:
			Texture2D();
			~Texture2D();

			void Generate(glm::ivec2 texSize, glm::ivec2 m_texWrap, GLuint internalFormat, GLuint imageFormat, GLuint type, unsigned char* data);
			void Generate(GLuint width, GLuint height, unsigned char* data, bool alpha = false);
			void Generate(const std::string& texturePath, bool alpha = false);
			void Update(const std::string& texturePath, bool alpha = false);
			void Update(GLuint width, GLuint height, unsigned char* data, bool alpha = false);		
			void Update(GLuint width, GLuint height, std::vector<unsigned char*> data, bool alpha = false);


			void Bind() const;		

		private:
			
			glm::ivec2 m_texSize; //width, height
			glm::ivec2 m_texFilter; //min, max
			glm::ivec2 m_texWrap; //S, T
			GLuint m_internalFormat; // Format of texture object
			GLuint m_imageFormat; // Format of loaded image	
			GLuint m_type;
		};
	}
}
#endif