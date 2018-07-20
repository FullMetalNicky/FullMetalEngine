#ifndef IOBJECT_H_
#define IOBJECT_H_

#include "TransformComponent.h"
#include <memory>
#include <map>
#include <vector>

namespace FME
{
	namespace Graphics
	{	
		/** \class IObject
		*  \brief An interface class for objects - every object must have a transform component.
		*/

		class IObject
		{
		public:
			
			IObject();
			virtual ~IObject() {};

			virtual void Draw() = 0;
			virtual void Update(double deltaTime) = 0;

			virtual std::shared_ptr<TransformComponent> GetTransformComponent();
			virtual std::map<std::string, std::shared_ptr<IObject>>  GetChildren() { return std::map<std::string, std::shared_ptr<IObject>>(); };
			std::string GetName() const { return m_name; };

			virtual void AddComponent(std::shared_ptr<IComponent> component);

		protected:
			
			std::string m_name;
			std::vector<std::shared_ptr<IComponent>> m_components;

		};
	}
}

#endif

