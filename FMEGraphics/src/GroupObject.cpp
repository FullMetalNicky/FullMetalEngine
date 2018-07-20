#include "GroupObject.h"
#include <iterator>


using namespace FME::Graphics;

GroupObject::GroupObject(const std::string& goName)
{
	m_name = goName;
}


void GroupObject::Draw()
{	
	for (std::map<std::string, std::shared_ptr<IObject>>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{		
		it->second->Draw();
	}
}

void GroupObject::Update(double deltaTime)
{	
	for (std::map<std::string, std::shared_ptr<IObject>>::iterator it = m_children.begin(); it != m_children.end(); ++it)
	{
		it->second->Update(deltaTime);
	}
}




std::shared_ptr<IObject>  GroupObject::GetChild(std::string childName)
{
	return m_children[childName];
}

void GroupObject::RemoveChild(std::string childName)
{
	m_children.erase(childName);
}

void GroupObject::AddChild(std::string childName, std::shared_ptr<GameObject> object)
{
	m_children[childName] = object;
}

void GroupObject::SetParent(std::shared_ptr<IObject> parent)
{
	m_parent = parent;
}