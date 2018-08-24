#ifndef PARTICLEBUOYANCY_H_
#define PARTICLEBUOYANCY_H_

#include "IParticleForce.h"

namespace FME
{
	namespace Simulation
	{
		class ParticleBuoyancy : public IParticleForce
		{
		public:

			ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity = 1000.0f);

			virtual void Update(std::shared_ptr<Particle> particle, float deltaTime);

		private:

			float m_maxDepth;
			float m_volume;
			float m_waterHeight;
			float m_liquidDensity;
		};
	}
}

#endif

