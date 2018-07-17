#pragma once

#include <glm/glm.hpp>

/** \class IPhysicalForce
*  \brief Interface for all forces to inherit from 
*  
*/

namespace FME
{
	namespace Simulation
	{
		class PhysicalModel;

		class IPhysicalForce
		{
		public:

			/** \brief getForces
			* \details This function calculates the forces.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const = 0;
		};
	}
}
