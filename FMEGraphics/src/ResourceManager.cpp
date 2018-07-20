#include "ResourceManager.h"
#include "Texture2D.h"
#include "Texture3D.h"

using namespace FME::Graphics;


std::shared_ptr<ResourceManager> ResourceManager::m_instance = nullptr;



std::shared_ptr<ResourceManager> ResourceManager::Instance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<ResourceManager>(new ResourceManager());
	}
	return m_instance;
}

ResourceManager::ResourceManager()
{

}



void   ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shader s(vShaderFile, fShaderFile);
	s.CompileShader();
	s.LinkShader();
	m_shaders[name] = s;
}

void ResourceManager::LoadTexture(const std::shared_ptr<ITexture>& t, std::string name)
{
	m_textures[name] = t;
}

void ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	std::shared_ptr<Texture2D> t(new Texture2D);
	t->Generate(file, alpha);
	t->SetName(name);
	m_textures[name] = t;
}

void ResourceManager::LoadTexture(const std::vector<std::string>& files, GLboolean alpha, std::string name)
{
	std::shared_ptr<Texture3D> t(new Texture3D);
	t->Generate(files, alpha);
	t->SetName(name);
	m_textures[name] = t;
}

void ResourceManager::LoadTexture(GLuint width, GLuint height, unsigned char* data, bool alpha, std::string name)
{
	std::shared_ptr<Texture2D> t(new Texture2D);
	t->Generate(width, height, data, alpha);
	t->SetName(name);
	m_textures[name] = t;
}

void ResourceManager::LoadModel(const std::shared_ptr<IModel>& model, std::string name)
{
	m_models[name] = model;
}

Shader ResourceManager::GetShader(std::string name) 
{
	return m_shaders[name];
}

std::shared_ptr<ITexture> ResourceManager::GetTexture(std::string name)
{
	return m_textures[name];
}

std::shared_ptr<IModel> ResourceManager::GetModel(std::string name)
{
	return m_models[name];
}


ResourceManager::~ResourceManager()
{

}