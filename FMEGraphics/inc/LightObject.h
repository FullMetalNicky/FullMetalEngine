#ifndef LIGHTOBJECT_H_
#define LIGHTOBJECT_H_

#include "IObject.h"


namespace FME
{
	namespace Graphics
	{
		class LightObject : public IObject
		{
		public:
			LightObject(const std::string& shaderName);

			virtual void Draw() = 0;

			virtual void Update(double deltaTime) {};

			virtual ~LightObject() {};

		private:

			std::string m_shaderName;
		};
	}
}


#endif