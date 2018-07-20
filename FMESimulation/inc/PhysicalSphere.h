#pragma once
#include "IPhysicalTrajectory.h"

/** \class PhysicalSphere
*  \brief Inherits from IPhysicalTrajectory interface. Implements a sphere on which the subject moves upon.
*/

namespace FME
{
	namespace Simulation
	{
		class PhysicalSphere : public IPhysicalTrajectory
		{
		public:

			/** \brief PhysicalSphere
			* \details a constructor.
			*
			* \param sensitivity float  sensitivity factor for moving on the sphere
			* \param cutoffAngles glm::vec2  angle limitations(minimum angle, maximum angle) that restrict access to poles
			*
			* \return void
			*/

			PhysicalSphere(float sensitivity = 0.05f, glm::vec2 cutoffAngles = glm::vec2(0.0f, 180.f));

			/** \brief calculateTrajectory
			* \details calculates the progress along the trajectory.
			*
			* \param deltaPos glm::vec3  change in position as result of the forces for each axis
			* \param currPos glm::vec3  current camera position
			* \param POI glm::vec3
			*
			* \return glm::vec3  next position of the object
			*/

			virtual glm::vec3 calculateTrajectory(glm::vec3 deltaPos, glm::vec3 currPos, glm::vec3 POI = glm::vec3(0.0f, 0.0f, 0.0f)) override;

		private:
			float m_sensitivity;
			glm::vec2 m_cutoffAngles;
		};
	}
}