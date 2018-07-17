#include "IPhysicalTrajectory.h"

/** \class PhysicalPSPlane
*  \brief Inherits from IPhysicalTrajectory interface. Implements a playstation-like plane on which the subject moves upon.
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalPSPlane : public IPhysicalTrajectory
		{
		public:

			/** \brief PhysicalPSPlane
			* \details a constructor.
			*
			* \param POI bool  inidicates if the movement is for the POI or the camera's position
			*
			* \return void
			*/

			PhysicalPSPlane(bool POI = false);

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
			bool m_POI;
		};
	}
}



