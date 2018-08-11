#ifndef PARTICLECONTACT_H_
#define PARTICLECONTACT_H_

#include "IParticleForce.h"
#include <vector>

namespace FME
{
	namespace Simulation
	{
		class ParticleContact : public IParticleForce
		{
		public:

			ParticleContact();

			virtual void Update(float deltaTime);

		protected:

			float calculateSeparatingVelocity() const;

		private:

			void resolveVelocity(float deltaTime);
			void resolveInterpenetration(float deltaTime);

			std::vector<std::shared_ptr<Particle>> m_particles;
			glm::vec3 m_contactNormal;
			float m_restitution;
			float m_penetration;
		};
	}
}

#endif


