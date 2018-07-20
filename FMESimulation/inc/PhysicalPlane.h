#pragma once
#include "IPhysicalTrajectory.h"

/** \class PhysicalPlane
*  \brief Inherits from IPhysicalTrajectory interface. Implements a regular plane on which the subject moves upon.
*/

namespace FME
{
	namespace Simulation
	{
		class PhysicalPlane : public IPhysicalTrajectory
		{
		public:

			/** \brief getForces
			* \details This function calculates the forces as results of the friction.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 calculateTrajectory(glm::vec3 deltaPos, glm::vec3 currPos, glm::vec3 POI = glm::vec3(0.0f, 0.0f, 0.0f)) override;
		};
	}
}