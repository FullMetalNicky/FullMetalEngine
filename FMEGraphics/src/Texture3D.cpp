#include "Texture3D.h"

#include <SOIL.h>

#include <iostream>

using namespace FME::Graphics;


Texture3D::Texture3D() : m_texSize(glm::ivec2(0)), m_texFilter(glm::ivec2(GL_LINEAR)), m_texWrap(glm::ivec2(GL_REPEAT)), m_internalFormat(GL_RGB), m_imageFormat(GL_RGB)
{
	glGenTextures(1, &m_texID);
}

void Texture3D::Generate(GLuint width, GLuint height, const std::vector<std::vector<unsigned char>>& dataVec, bool alpha)
{
	m_texSize.x = width;
	m_texSize.y = height;

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);

	if (alpha)
	{
		m_internalFormat = GL_RGBA;
		m_imageFormat = GL_RGBA;
	}
	for (unsigned int i = 0; i < dataVec.size(); i++)
	{
		unsigned char* image = const_cast<unsigned char*>(dataVec[i].data());
		if (image)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_internalFormat, width, height, 0, m_imageFormat, GL_UNSIGNED_BYTE, image);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at index: " << i << std::endl;
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, m_texWrap.x);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, m_texWrap.y);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, m_texFilter.x);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, m_texFilter.y);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture3D::Generate(const std::vector<std::string>& texturePathVec, bool alpha)
{
	std::vector<std::vector<unsigned char>> dataVec;
	unsigned char* releaseMem[6];
	int width, height;
	for (unsigned int i = 0; i < texturePathVec.size(); i++)
	{
		unsigned char* image = SOIL_load_image(texturePathVec[i].c_str(), &width, &height, 0, alpha == false ? SOIL_LOAD_RGB : SOIL_LOAD_RGBA);
		size_t size = width * height * (alpha == false ? 3 : 4);
		releaseMem[i] = image;
		dataVec.push_back(std::vector<unsigned char>(image, image + size));
	}
	Generate(width, height, dataVec, alpha);
	for (unsigned int i = 0; i < dataVec.size(); i++)
	{
		SOIL_free_image_data(releaseMem[i]);
	}
}

void Texture3D::Update(GLuint width, GLuint height, std::vector<unsigned char*> data, bool alpha)
{
	if (data.size() == 6)
	{
		for (unsigned int i = 0; i < data.size(); i++)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, 0, width, height, m_internalFormat, GL_UNSIGNED_BYTE, data[i]);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
}


void Texture3D::Bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);
}

Texture3D::~Texture3D()
{
	glDeleteTextures(1, &m_texID);
}
