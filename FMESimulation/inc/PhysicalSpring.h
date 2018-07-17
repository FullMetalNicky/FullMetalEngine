#pragma once
#include "IPhysicalForce.h"
#include "PhysicalModel.h"

/** \class PhysicalSpring
*  \brief Inherits from IPhysicalForce interface. Implements a regular spring.
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalSpring : public IPhysicalForce
		{
		public:

			/** \brief PhysicalSpring
			* \details a constructor.
			*
			* \param range glm::vec3  vec3 of range(per axis)
			* \param springConstant glm::vec3  spring constants that match the range elements respectively
			*
			* \return void
			*/

			PhysicalSpring(glm::vec3 range, glm::vec3 springConstant);

			/** \brief getForces
			* \details This function calculates the forces as results of the spring.
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