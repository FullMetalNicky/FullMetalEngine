#ifndef PARTICLEDRAG_H_
#define PARTICLEDRAG_H_

#include "IParticleForce.h"

namespace FME
{
	namespace Simulation
	{
		class ParticleDrag : public IParticleForce
		{
		public:

			ParticleDrag(const glm::vec2& kCoeffs);

			virtual void Update(std::shared_ptr<Particle> particle, float deltaTime);

		private:

			glm::vec2 m_kCoeffs;

		};
	}
}

#endif

