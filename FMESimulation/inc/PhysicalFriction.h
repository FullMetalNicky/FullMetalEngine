#pragma once
#include "IPhysicalForce.h"
#include "PhysicalModel.h"

/** \class PhysicalFriction
*  \brief Inherits from IPhysicalForce interface. Implements regular friction.
*/

namespace FME
{
	namespace Simulation
	{
		class PhysicalFriction : public IPhysicalForce
		{
		public:

			/** \brief PhysicalFriction
			* \details a constructor.
			*
			* \param normal float  force exerted on the object by the surface
			* \param frictionCoefficient glm::vec3  friction coefficiant for each axis
			*
			* \return void
			*/

			PhysicalFriction(float normal, glm::vec3 frictionCoefficient);

			/** \brief getForces
			* \details This function calculates the forces as results of the friction.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;

		private:
			float m_normal;
			glm::vec3 m_frictionCoefficient;
		};
	}
}