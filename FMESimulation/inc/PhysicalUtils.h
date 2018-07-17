#pragma once
#include <glm/glm.hpp>


/** \class PhysicalUtils
*  \brief class that implements frequently used general methods
*
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalUtils
		{
		public:

			/** \brief sphereicalToCartesian
			* \details converts between coordinate systems
			*
			* \param coords glm::vec3  coordinates vector of the following format (radius, theta, phi)
			*
			* \return coords glm::vec3 coordinates (x,y,z)
			*/

			static glm::vec3 sphereicalToCartesian(glm::vec3 coords);

			/** \brief CartesianToSphereical
			* \details converts between coordinate systems
			*
			* \param coords glm::vec3  coordinates (x,y,z)
			*
			* \return coords glm::vec3 coordinates vector of the following format (radius, theta, phi)
			*/

			static glm::vec3 cartesianToSphereical(glm::vec3 coords);

			/** \brief cartesianToSphereicalAbsolute
			* \details converts between coordinate systems after centralizing aroung the offset
			*
			* \param coords glm::vec3  coordinates vector of the following format (radius, theta, phi)
			*
			* \return coords glm::vec3 coordinates (x,y,z)
			*/

			static glm::vec3 translateVector(glm::vec3 pos, glm::vec3 offset);


			static void printVec3(glm::vec3);
		};
	}
}