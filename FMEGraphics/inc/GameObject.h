#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "IObject.h"
#include "IModel.h"

namespace FME
{
	namespace Graphics
	{
		/** \class GameObject
		*  \brief A  class that implements an object's leaf. Currently GameObject has no children. GameObject holds the geomteric model of a drawable 
		* and though IObject also has the transform component. 
		*/

		class GameObject : public IObject
		{
		public:

			GameObject(const std::string& goName = "");
			virtual ~GameObject() {};

			virtual void Draw();
			
			virtual void Update(double deltaTime);
		
			virtual std::map<std::string, std::shared_ptr<IObject>>  GetChildren() { return std::map<std::string, std::shared_ptr<IObject>>(); };

		private:

		};
	}
}

#endif