#ifndef PARTICLEGRAVITY_H_
#define PARTICLEGRAVITY_H_

#include "IParticleForce.h"

namespace FME
{
	namespace Simulation
	{
		class ParticleGravity : public IParticleForce
		{
		public:

			ParticleGravity(const glm::vec3& gravity);

			virtual void Update(std::shared_ptr<Particle> particle, float deltaTime);

		private:

			glm::vec3 m_gravity;

		};
	}
}

#endif
