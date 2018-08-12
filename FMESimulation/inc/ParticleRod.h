#ifndef PARTICLEROD_H_
#define PARTICLEROD_H_

#include "ParticleLink.h"

namespace FME
{
	namespace Simulation
	{
		class ParticleRod : public ParticleLink
		{
		public:

			virtual bool AddContact(std::shared_ptr<ParticleContact> particleContact);

		protected:

			float m_length;
		};
	}
}

#endif

