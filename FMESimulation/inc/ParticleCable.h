#ifndef PARTICLECABLE_H_
#define PARTICLECABLE_H_

#include "ParticleLink.h"

namespace FME
{
	namespace Simulation
	{
		class ParticleCable : public ParticleLink
		{
		public:
			
			virtual bool AddContact(std::shared_ptr<ParticleContact> particleContact);

		protected:

			float m_maxLength;
			float m_restitution;
		};
	}
}

#endif
