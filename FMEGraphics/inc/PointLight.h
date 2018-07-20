#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "LightObject.h"


namespace FME
{
	namespace Graphics
	{
		struct PointLightInfo {
			glm::vec3 position;
			float constant;
			float linear;
			float quadratic;
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;
		};

		class PointLight : public LightObject
		{
		public:
			PointLight(const std::string& shaderName, const std::vector<PointLightInfo>& lightsInfo);

			virtual void Draw();

			virtual void Update(double deltaTime) {};

			virtual ~PointLight() {};

		private:

			std::string parseShaderParam(const std::string& paramName, int index);

			std::string m_shaderName;
			std::vector<PointLightInfo> m_pointLightsInfo;
		};
	}
}


#endif