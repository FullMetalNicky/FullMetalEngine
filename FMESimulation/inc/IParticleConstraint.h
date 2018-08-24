#ifndef IPARTICLECONSTRAINT_H_
#define IPARTICLECONSTRAINT_H_

#include "ParticleContact.h"
#include <vector>
#include <memory>

namespace FME
{
	namespace Simulation
	{
		class IParticleConstraint
		{
		public:

			virtual bool AddContact(std::shared_ptr<ParticleContact> particleContact) = 0;

		protected:

			std::vector<std::shared_ptr<Particle>> m_particles;
		};
	}
}

#endif
