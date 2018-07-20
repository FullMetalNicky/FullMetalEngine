#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "LightObject.h"


namespace FME
{
	namespace Graphics
	{
		class SpotLight : public LightObject
		{
		public:
			SpotLight(const std::vector<LightInfo>& lightsInfo);

			virtual void Draw();

			virtual void Update(double deltaTime) {};

			virtual ~SpotLight() {};

		private:

			std::string parseShaderParam(const std::string& paramName, int index);
			std::vector<LightInfo> m_spotLightsInfo;
		};
	}
}


#endif