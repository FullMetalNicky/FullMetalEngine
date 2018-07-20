#include "IPhysicalForce.h"
#include "PhysicalModel.h"

namespace FME
{
	namespace Simulation
	{
		class PhysicalTimedAngularAcceleration : public IPhysicalForce
		{
		public:

			PhysicalTimedAngularAcceleration(glm::vec3 target, float duration);

			/*
			Parameters:
			The function recieves rigidBody element and the time difference since the last calculation
			Rreturn value:
			Vec3 containing the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;

		private:

			glm::vec3 m_target;
			mutable glm::vec3 m_acceleration;
			mutable float m_duration;
			mutable bool m_init;
		};
	}
}