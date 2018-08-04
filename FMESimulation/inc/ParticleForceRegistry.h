#ifndef PARTICLEFORCEREGISTRY_H_
#define PARTICLEFORCEREGISTRY_H_

#include "IParticleForce.h"
#include <vector>

namespace FME
{
	namespace Simulation
	{
		class ParticleForceRegistry
		{
		public:

			void Update(float deltaTime);

			void Clear();

			void Add(std::shared_ptr<Particle> particle, std::shared_ptr<IParticleForce> particleForce);

			void Remove(std::shared_ptr<Particle> particle, std::shared_ptr<IParticleForce> particleForce);


		protected:

			struct ParticleForceRegistration
			{
				std::shared_ptr<Particle> particle;
				std::shared_ptr<IParticleForce> particleForce;
			};

			std::vector<ParticleForceRegistration> m_registrations; 
			//not sure this is the right way to organize it. 
			//Lots of duplications for particles with many forces or forces with many particles.
			//might want to do like a hash table for particles or forces.

		};
	}
}

#endif





