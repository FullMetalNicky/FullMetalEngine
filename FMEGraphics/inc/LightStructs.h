#ifndef LIGHTSTRUCTS_H_
#define LIGHTSTRUCTS_H_

#include <glm/glm.hpp>

namespace FME
{
	namespace Graphics
	{
		struct DirLight {
			glm::vec3 direction;
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;
		};

		struct PointLight {
			glm::vec3 position;
			float constant;
			float linear;
			float quadratic;
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;
		};

		struct SpotLight {
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

	}
}

#endif