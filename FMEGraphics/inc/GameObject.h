#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "IComponent.h"
#include <map>
#include <memory>
#include <vector>

namespace FME
{
	namespace Graphics
	{
		/** \class GameObject
		*  \brief A  class that implements an object's leaf. Currently GameObject has no children. GameObject holds the geomteric model of a drawable 
		* and though IObject also has the transform component. 
		*/

		class GameObject 
		{
		public:

			GameObject(const std::string& goName = "");

			virtual ~GameObject() {};

			virtual void Draw();
			
			virtual void Update(double deltaTime);
		
			virtual std::map<std::string, std::shared_ptr<GameObject>>  GetChildren() { return m_children; };

			virtual void RemoveChild(std::string childName);

			virtual void AddChild(std::string childName, std::shared_ptr<GameObject> object);

			virtual void SetParent(std::shared_ptr<GameObject> parent);

			virtual std::shared_ptr<IComponent> GetComponentByType(const std::string& type);

			virtual void AddComponent(std::shared_ptr<IComponent> component);

			std::string GetName() const { return m_name; };

		protected:

			std::string m_name;
			std::vector<std::shared_ptr<IComponent>> m_components;
			std::map<std::string, std::shared_ptr<GameObject>> m_children;
			std::shared_ptr<GameObject> m_parent;
		};
	}
}

#endif