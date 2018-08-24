#ifndef PARTICLESPRING_H_
#define PARTICLESPRING_H_

#include "IParticleForce.h"

namespace FME
{
	namespace Simulation
	{
		class ParticleSpring : public IParticleForce
		{
		public:

			ParticleSpring(std::shared_ptr<Particle> otherParticle, float coeff, float restLength);

			virtual void Update(std::shared_ptr<Particle> particle, float deltaTime);

		private:

			std::shared_ptr<Particle> m_otherParticle;
			float m_coeff; //spring constant
			float m_restLength;
		};
	}
}

#endif

