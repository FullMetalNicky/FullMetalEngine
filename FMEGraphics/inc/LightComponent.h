#ifndef LIGHTCOMPONENT_H_
#define LIGHTCOMPONENT_H_


#include "IComponent.h"
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

			void SetShader(const std::string& shaderName);

			void Draw();

			virtual ~LightComponent() {};

		private:

			std::string m_shaderName;
			std::vector<std::shared_ptr<LightObject>> m_lights;
		};
	}
}



#endif