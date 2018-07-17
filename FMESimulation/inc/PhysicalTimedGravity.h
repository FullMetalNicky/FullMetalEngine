#include "IPhysicalForce.h"
#include "PhysicalModel.h"

namespace FME
{
	namespace Simulation
	{
		class PhysicalTimedGravity : public IPhysicalForce
		{
		public:

			/*
				Parameters:
					The function recieves vec3 with the position of center of mass, float for mass, float for the
					duration of the force's effect, and vec2 (minimum radius, maximum radius), that limits the
					force's range.
			*/

			PhysicalTimedGravity(glm::vec3 center, float mass, float duration, glm::vec2 radiusRange = glm::vec2(0.0f, HUGE_VALF));

			/*
			Parameters:
			The function recieves rigidBody element and the time difference since the last calculation
			Rreturn value:
			Vec3 containing the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;

		private:
			glm::vec3 m_center;
			float m_mass;
			mutable float m_duration;
			glm::vec2 m_radiusRange;
		};
	}
}