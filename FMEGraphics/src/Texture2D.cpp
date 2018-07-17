#include "Texture2D.h"
#include <SOIL.h>

#include <iostream>

using namespace FME::Graphics;


Texture2D::Texture2D() : m_texSize(glm::ivec2(0)), m_texFilter(glm::ivec2(GL_LINEAR)), m_texWrap(glm::ivec2(GL_REPEAT)), m_internalFormat(GL_RGB), m_imageFormat(GL_RGB)
{
	glGenTextures(1, &m_texID);
}


void Texture2D::Generate(glm::ivec2 texSize, glm::ivec2 m_texWrap, GLuint internalFormat, GLuint imageFormat, GLuint type, unsigned char* data)
{
	m_texSize = texSize;
	glBindTexture(GL_TEXTURE_2D, m_texID);

	m_internalFormat = internalFormat;
	m_imageFormat = imageFormat;
	m_type = type;

	glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_texSize.x, m_texSize.y, 0, m_imageFormat, m_type, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texWrap.x);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texWrap.y);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texFilter.x);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texFilter.y);

	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture2D::Generate(GLuint width, GLuint height, unsigned char* data, bool alpha) 
{
	m_texSize.x = width;
	m_texSize.y = height;

	glBindTexture(GL_TEXTURE_2D, m_texID);

	if (alpha)
	{
		m_internalFormat = GL_RGBA;
		m_imageFormat = GL_RGBA;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, width, height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texWrap.x);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texWrap.y);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texFilter.x);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texFilter.y);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Generate(const std::string& texturePath, bool alpha)
{
	int width, height;
	unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, alpha == false ? SOIL_LOAD_RGB: SOIL_LOAD_RGBA);
	Generate(width, height, image, alpha);
	SOIL_free_image_data(image);
}

void Texture2D::Update(const std::string& texturePath, bool alpha)
{
	int width, height;
	unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, alpha == false ? SOIL_LOAD_RGB : SOIL_LOAD_RGBA);
	Update(width, height, image, alpha);
	SOIL_free_image_data(image);
}

void Texture2D::Update(GLuint width, GLuint height, unsigned char* data, bool alpha)
{
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, m_internalFormat, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Update(GLuint width, GLuint height, std::vector<unsigned char*> data, bool alpha)
{
	if (data.size() == 1)
	{
		Update(width, height, data[0], alpha);
	}
}


void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texID);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_texID);
}
