#include "ParticleRod.h"

using namespace FME::Simulation;


bool ParticleRod::AddContact(std::shared_ptr<ParticleContact> particleContact)
{
	bool res = false;

	float currLength = getCurrentLinkLength();
	if (currLength != m_length)
	{
		particleContact->SetParticle(m_particles[0], 0);
		particleContact->SetParticle(m_particles[1], 1);

		glm::vec3 normal = getContactNormal();
		float diffLength = currLength - m_length;

		if (currLength > m_length)
		{
			particleContact->SetContactNormal(normal);
			particleContact->SetPenetration(diffLength);
		}
		else
		{
			particleContact->SetContactNormal(-1.0f * normal);
			particleContact->SetPenetration(-1.0f * diffLength);
		}

		particleContact->SetRestitution(0.0f);
		res = true;
	}

	return res;
}
