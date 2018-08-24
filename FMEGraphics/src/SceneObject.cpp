#include "SceneObject.h"
#include "GameObject.h"
#include "SkyboxModel.h"
#include "GeometryModel.h"
#include "OBJModel.h"
#include "GeometryMesh.h"
#include "ResourceManager.h"
#include "SceneLoader.h"

using namespace FME::Graphics;


SceneObject::SceneObject(const std::string& jsonPath)
{
	m_gameLevel = 0;

	SceneLoader sl(jsonPath);
	sl.LoadAssets();
	sl.LoadLevels(m_children);
}


void SceneObject::Update(double deltaTime)
{	
	for (int i = 0; i < m_children[m_gameLevel].size(); ++i)
	{
		m_children[m_gameLevel][i]->Update(deltaTime);
	}
}

void SceneObject::Draw()
{
	for (int i = 0; i < m_children[m_gameLevel].size(); ++i)
	{
		m_children[m_gameLevel][i]->Draw();
	}
}

void SceneObject::SetGameLevel(unsigned int gameLevel)
{
	m_gameLevel = gameLevel;
}