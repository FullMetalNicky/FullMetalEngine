#pragma once
#include <glm/glm.hpp>


/** \class IPhysicalTrajectory
*  \brief Interface for all trajectories to inherit from
*
*/

namespace FME
{
	namespace Simulation
	{
		class IPhysicalTrajectory
		{
		public:

			/** \brief getForces
			* \details This function calculates the forces as results of the angular friction.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 calculateTrajectory(glm::vec3 deltaPos, glm::vec3 currPos, glm::vec3 POI = glm::vec3(0.0f, 0.0f, 0.0f)) = 0;
		};
	}
}