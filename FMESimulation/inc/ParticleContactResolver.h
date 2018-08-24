#ifndef PARTICLECONTACTRESOLVER_H_
#define PARTICLECONTACTRESOLVER_H_

#include "ParticleContact.h"

namespace FME
{
	namespace Simulation
	{
		class ParticleContactResolver
		{
		public:
			ParticleContactResolver(unsigned int iterations);

			void SetIterations(unsigned int iterations);

			void Update(const std::vector<std::shared_ptr<ParticleContact>>& particleContacts, float deltaTime);

		protected:
			unsigned int m_iterations;
			unsigned int m_usedIterations;

		private:
			unsigned int findMostSevereContact(const std::vector<std::shared_ptr<ParticleContact>>& particleContacts);
		};

	}
}


#endif