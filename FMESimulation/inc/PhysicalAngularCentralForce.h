#pragma once
#include "IPhysicalForce.h"
#include "PhysicalModel.h"


/** \class PhysicalAngularCentralForce
*  \brief Inherits from IPhysicalForce interface. Implements central force that effect the POI.
*/

namespace FME
{
	namespace Simulation
	{
		class PhysicalAngularCentralForce : public IPhysicalForce
		{
		public:

			/** \brief PhysicalAngularCentralForce
			* \details a constructor.
			*
			* \param center glm::vec3  position of the force inducing body
			* \param mass float  mass of the force inducing body
			* \param radiusRange glm::vec2  radius range where the force is effective in the for of (mininum radius, maximum radius)
			*
			* \return void
			*/

			PhysicalAngularCentralForce(glm::vec3 center, float mass, glm::vec2 radiusRange = glm::vec2(0.0f, HUGE_VALF));

			/** \brief getForces
			* \details This function calculates the forces as results of the force.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;

		private:
			glm::vec3 m_center;
			float m_mass;
			glm::vec2 m_radiusRange;
		};
	}
}