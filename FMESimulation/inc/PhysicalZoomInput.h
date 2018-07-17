#include "IPhysicalForce.h"

/** \class PhysicalSwipeInput
*  \brief Inherits from IPhysicalForce interface. This class represents force that comes from user input such as mouse move or touch gesture
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalZoomInput : public IPhysicalForce
		{
			/** \brief getForces
			* \details This function calculates the forces as results of the rotational spring.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;
		};
	}
}