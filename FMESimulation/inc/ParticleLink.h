#ifndef PARTICLELINK_H_
#define PARTICLELINK_H_

#include "IParticleConstraint.h"

namespace FME
{
	namespace Simulation
	{		      
		class ParticleLink : public IParticleConstraint
		{
		public:

			ParticleLink();

			virtual bool AddContact(std::vector<std::shared_ptr<ParticleContact>> particleContact) = 0;

		protected:

			float getCurrentLinkLength() const;
			glm::vec3 getContactNormal() const;
		};
	}
}

#endif
