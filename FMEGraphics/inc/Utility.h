#ifndef UTILITY_H_
#define UTILITY_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL.h>
#include <glm\glm.hpp> 
#include "glm/gtx/string_cast.hpp"

namespace FME
{
	namespace Graphics
	{
		/** \class Utility
		*  \brief A class gathering static methods that are for general use. 
		*/

		class Utility
		{
		public:
			template <class T>
			static void printVec(T vec)
			{
				std::cout << glm::to_string(vec) << std::endl;
			}

			static GLuint loadTexture(GLchar* path);
		};
	}
}
#endif

