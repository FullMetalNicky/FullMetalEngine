#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "LightObject.h"


namespace FME
{
	namespace Graphics
	{
		class PointLight : public LightObject
		{
		public:
			PointLight(const std::vector<LightInfo>& lightsInfo);

			virtual void Draw();

			virtual void Update(double deltaTime) {};

			virtual ~PointLight() {};

		private:

			std::string parseShaderParam(const std::string& paramName, int index);
			std::vector<LightInfo> m_pointLightsInfo;
		};
	}
}


#endif