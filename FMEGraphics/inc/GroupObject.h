#ifndef GROUPOBJECT_H_
#define GROUPOBJECT_H_

#include "GameObject.h"
#include <map>

namespace FME
{
	namespace Graphics
	{
		/** \class GroupObject
		*  \brief A  class that implements a group object, containing several IObjects and allowing for hierarchy between their transform components
		*/

		class GroupObject : public IObject
		{
		public:

			GroupObject(const std::string& goName = "");
			virtual ~GroupObject() {};

			virtual void Draw();
			virtual void Update(double deltaTime);

			virtual std::shared_ptr<IObject> GetChild(std::string childName);
			virtual std::map<std::string, std::shared_ptr<IObject>>  GetChildren() { return m_children; };

			void RemoveChild(std::string childName);
			void AddChild(std::string childName, std::shared_ptr<GameObject> object);
			void SetParent(std::shared_ptr<IObject> parent);


		private:
			std::map<std::string, std::shared_ptr<IObject>> m_children;
			std::shared_ptr<IObject> m_parent;
		};
	}
}

#endif
