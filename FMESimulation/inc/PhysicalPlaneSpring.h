#pragma once

#include "IPhysicalForce.h"

/** \class PhysicalPlaneSpring
*  \brief Inherits from IPhysicalForce interface. Implements a specific planar spring.
*/

namespace FME
{
	namespace Simulation
	{
		class PhysicalPlaneSpring : public IPhysicalForce
		{
		public:
			/** \brief PhysicalPlaneSpring
			* \details a constructor.
			*
			* \param range glm::vec3  vec3 of range(per axis)
			* \param springConstant glm::vec3  spring constants that match the range elements respectively
			*
			* \return void
			*/

			PhysicalPlaneSpring(glm::vec3 range, glm::vec3 springConstant);

			/** \brief getForces
			* \details This function calculates the forces as results of the plane spring.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;

		private:
			glm::vec3 m_range;
			glm::vec3 m_springConstant;
		};
	}
}