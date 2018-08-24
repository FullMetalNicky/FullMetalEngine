#ifndef PARTICLEWORLD_H_
#define PARTICLEWORLD_H_

#include "ParticleForceRegistry.h"
#include"ParticleContactResolver.h"
#include "IParticleConstraint.h"

namespace FME
{
	namespace Simulation
	{
		class ParticleWorld
		{
		public:

			ParticleWorld(unsigned int maxContacts, unsigned int iterations = 0);

			void Update(float deltaTime);

			void ClearFrame();

		protected:

			void integrate(float deltaTime);
			unsigned int generateContacts();


			std::vector<std::shared_ptr<Particle>> m_particles;
			std::vector<std::shared_ptr<ParticleContact>> m_particleContacts;
			std::vector<std::shared_ptr<IParticleConstraint>> m_particleConnstraints;
			ParticleForceRegistry m_registry;
			ParticleContactResolver m_resolver;


			unsigned int m_maxContacts;
			bool m_calculateIterations;
		};
	}
}

#endif