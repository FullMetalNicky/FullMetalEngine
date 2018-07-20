#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "LightObject.h"


namespace FME
{
	namespace Graphics
	{
		class DirectionalLight : public LightObject
		{
		public:
			DirectionalLight(const std::vector<LightInfo>& lightsInfo);

			virtual void Draw();

			virtual void Update(double deltaTime) {};

			virtual ~DirectionalLight() {};

		private:

			std::string parseShaderParam(const std::string& paramName, int index);
			std::vector<LightInfo> m_dirLightsInfo;
		};
	}
}


#endif