#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "LightObject.h"


namespace FME
{
	namespace Graphics
	{
		struct DirLightInfo {
			glm::vec3 direction;
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;
		};

		class DirectionalLight : public LightObject
		{
		public:
			DirectionalLight(const std::string& shaderName, const std::vector<DirLightInfo>& lightsInfo);

			virtual void Draw();

			virtual void Update(double deltaTime) {};

			virtual ~DirectionalLight() {};

		private:

			std::string parseShaderParam(const std::string& paramName, int index);

			std::string m_shaderName;
			std::vector<DirLightInfo> m_dirLightsInfo;
		};
	}
}


#endif