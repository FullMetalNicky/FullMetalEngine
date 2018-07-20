#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "LightObject.h"


namespace FME
{
	namespace Graphics
	{
		struct SpotLightInfo {
			glm::vec3 position;
			glm::vec3 direction;
			float cutOff;
			float outerCutOff;
			float constant;
			float linear;
			float quadratic;
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;
		};

		class SpotLight : public LightObject
		{
		public:
			SpotLight(const std::string& shaderName, const std::vector<SpotLightInfo>& lightsInfo);

			virtual void Draw();

			virtual void Update(double deltaTime) {};

			virtual ~SpotLight() {};

		private:

			std::string parseShaderParam(const std::string& paramName, int index);

			std::string m_shaderName;
			std::vector<SpotLightInfo> m_spotLightsInfo;
		};
	}
}


#endif