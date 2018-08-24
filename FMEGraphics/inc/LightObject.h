#ifndef LIGHTOBJECT_H_
#define LIGHTOBJECT_H_

#include "GameObject.h"
#include <glm/glm.hpp>


namespace FME
{
	namespace Graphics
	{
		struct LightInfo {
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


		class LightObject : public GameObject
		{
		public:
			LightObject();

			virtual void Draw() = 0;

			virtual void Update(double deltaTime) {};

			virtual ~LightObject() {};

			void SetShader(const std::string& shaderName);

		protected:

			std::string m_shaderName;
		};
	}
}


#endif