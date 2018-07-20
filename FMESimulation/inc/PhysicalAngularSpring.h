#include "IPhysicalForce.h"

namespace FME
{
	namespace Simulation
	{
		class PhysicalAngularSpring : public IPhysicalForce
		{
		public:
			/*
			Parameters:
			The function recieves a vec2 of range(minimum angle, maximum angle)
			and vec2 of spring constants that match the range elements respectively.
			*/

			PhysicalAngularSpring(glm::vec2 range, glm::vec2 springConstant);

			/*
			Parameters:
			The function recieves physicalModel element and the time difference since the last calculation
			Rreturn value:
			Vec3 containing the forces acting on the object on each axis as a result from the radial spring
			*/
			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;

		private:
			glm::vec2 m_range;
			glm::vec2 m_springConstant;
		};
	}
}