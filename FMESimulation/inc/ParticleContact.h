#ifndef PARTICLECONTACT_H_
#define PARTICLECONTACT_H_

#include "Particle.h"
#include <vector>
#include <memory>


namespace FME
{
	namespace Simulation
	{
		class ParticleContact 
		{
		public:

			ParticleContact();

			virtual void Update(float deltaTime);

			float CalculateSeparatingVelocity() const;

			float GetPenetration() const { return m_penetration; };

			std::shared_ptr<Particle> GetParticle(unsigned int index) const;

			void SetParticle(std::shared_ptr<Particle> particle, unsigned int index);

			void SetContactNormal(glm::vec3 normal) { m_contactNormal = normal; };

			void SetPenetration(float penetration) { m_penetration = penetration; };

			void SetRestitution(float restitution) { m_restitution = restitution; };


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


