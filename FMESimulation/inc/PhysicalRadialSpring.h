#pragma once
#include "IPhysicalForce.h"
#include "PhysicalModel.h"

/** \class PhysicalRadialSpring
*  \brief Inherits from IPhysicalForce interface. Implements a specific angular spring.
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalRadialSpring : public IPhysicalForce
		{
		public:

			/** \brief PhysicalRadialSpring
			* \details a constructor.
			*
			* \param range glm::vec2  vec2 of range(minimum radius, maximum radius)
			* \param springConstant glm::vec2  spring constants that match the range elements respectively
			*
			* \return void
			*/

			PhysicalRadialSpring(glm::vec2 range, glm::vec2 springConstant);

			/** \brief getForces
			* \details This function calculates the forces as results of the radial spring.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;

		private:
			glm::vec2 m_range;
			glm::vec2 m_springConstant;
		};
	}
}