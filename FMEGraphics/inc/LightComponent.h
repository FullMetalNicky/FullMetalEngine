#ifndef LIGHTCOMPONENT_H_
#define LIGHTCOMPONENT_H_


#include "IComponent.h"
#include "LightStructs.h"
#include "LightObject.h"
#include <GL/glew.h>


namespace FME
{
	namespace Graphics
	{
		class LightComponent : public IComponent
		{
		public:

			LightComponent(const std::vector<std::shared_ptr<LightObject>>& lights);

			void Draw();

			virtual ~LightComponent() {};

		private:

			std::vector<std::shared_ptr<LightObject>> m_lights;
		};
	}
}



#endif