
#include "Shader.h"

using namespace FME::Graphics;


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// 1. Retrieve the vertex/fragment source code from filePath

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		m_VertexCode = vShaderStream.str();
		m_FragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}


void Shader::CompileShader()
{
	CompileShaderImp(m_VertexID, m_VertexCode.c_str(), GL_VERTEX_SHADER);
	CompileShaderImp(m_FragmentID, m_FragmentCode.c_str(), GL_FRAGMENT_SHADER);
}


void Shader::CompileShaderImp(GLint& shaderID, const char* shaderText, GLuint shaderType)
{
	GLint success;
	GLchar infoLog[512];

	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderText, NULL);
	glCompileShader(shaderID);
	// Print compile errors if any
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::LinkShader()
{
	GLint success;
	GLchar infoLog[512];

	this->m_Program = glCreateProgram();
	glAttachShader(this->m_Program, m_VertexID);
	glAttachShader(this->m_Program, m_FragmentID);
	glLinkProgram(this->m_Program);
	// Print linking errors if any
	glGetProgramiv(this->m_Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->m_Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);
}

void Shader::Use()
{
	glUseProgram(this->m_Program);
}

void Shader::UnUse()
{
	glUseProgram(0);
}