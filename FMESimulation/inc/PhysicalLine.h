#include "IPhysicalTrajectory.h"

/** \class PhysicalLine
*  \brief Inherits from IPhysicalTrajectory interface. Implements a regular line on which the subject moves upon.
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalLine : public IPhysicalTrajectory
		{
		public:

			/** \brief PhysicalLine
			* \details a constructor.
			*
			* \param range glm::vec2  limitation that restricts access to line ends
			* \param sensitivity float  sensitivity factor for moving on the sphere
			*
			* \return void
			*/

			PhysicalLine(glm::vec2 range = glm::vec2(0.0f, HUGE_VALF), float sensitivity = 0.05f);

			/** \brief getForces
			* \details This function calculates the forces as results of the friction.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 calculateTrajectory(glm::vec3 deltaPos, glm::vec3 currPos, glm::vec3 POI = glm::vec3(0.0f, 0.0f, 0.0f)) override;

		private:
			glm::vec2 m_range;
			float m_sensitivity;
		};
	}
}