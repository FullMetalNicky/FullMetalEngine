#include "ParticleCable.h"

using namespace FME::Simulation;


bool ParticleCable::AddContact(std::shared_ptr<ParticleContact> particleContact)
{
	bool res = false;

	float length = getCurrentLinkLength();
	if (length > m_maxLength)
	{
		particleContact->SetParticle(m_particles[0], 0);
		particleContact->SetParticle(m_particles[1], 1);

		particleContact->SetContactNormal(getContactNormal());
		particleContact->SetPenetration(length - m_maxLength);
		particleContact->SetRestitution(m_restitution);

		res = true;
	}

	return res;
}
