#ifndef ITEXTURE_H_
#define ITEXTURE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace FME
{
	namespace Graphics
	{
		/** \class ITexture
		*  \brief An interface class for all textures - 2D/3D, anything you can bind and get its ID
		*/

		class ITexture
		{
		public:
			virtual void Bind() const = 0;
			virtual void Update(GLuint width, GLuint height, unsigned char* data, bool alpha = false) {};
			virtual void Update(GLuint width, GLuint height, std::vector<unsigned char*> data, bool alpha = false) {};

			virtual ~ITexture() {};

			virtual GLuint GetTextureID() const { return m_texID; };

			virtual std::string GetType() const { return m_type; };
			virtual void SetType(const std::string& type) { m_type = type; };
			virtual std::string GetPath() const { return m_path; };
			virtual void SetPath(const std::string& path) { m_path = path; };
			virtual std::string GetName() const { return m_path; };
			virtual void SetName(const std::string& path) { m_path = path; };

		protected:		

			GLuint m_texID;
			std::string m_type;
			std::string m_path;
			std::string m_name;
		};
	}
}
#endif