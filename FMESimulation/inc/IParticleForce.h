#ifndef IPARTICLEFORCE_H_
#define IPARTICLEFORCE_H_

#include "Particle.h"
#include <memory>

namespace FME
{
	namespace Simulation
	{
		class IParticleForce
		{
		public:

			virtual void Update(std::shared_ptr<Particle> particle, float deltaTime) = 0;
					
		};
	}
}

#endif
