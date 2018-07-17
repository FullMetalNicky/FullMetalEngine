#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

namespace FME
{
	namespace Graphics
	{
		/** \class Shader
		*  \brief A class that reads shader files, compiles and links them. 
		*/

		class Shader
		{
		public:

			// Constructor reads and builds the shader
			void CompileShader();
			Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
			void LinkShader();
			Shader() {};
			// Use the program
			void Use();
			void UnUse();
			GLuint GetProgramID() const { return m_Program; };

		private:
			void CompileShaderImp(GLint& shaderID, const char* shaderText, GLuint shaderType);

			GLuint m_Program;
			std::string m_VertexCode;
			std::string m_FragmentCode;
			GLint m_VertexID;
			GLint m_FragmentID;
		};
	}
}
#endif
