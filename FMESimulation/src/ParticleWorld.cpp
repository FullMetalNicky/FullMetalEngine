#include "ParticleWorld.h"

using namespace FME::Simulation;

ParticleWorld::ParticleWorld(unsigned int maxContacts, unsigned int iterations) : m_resolver(iterations), m_maxContacts(maxContacts)
{
	m_particleContacts = std::vector<std::shared_ptr<ParticleContact>>(maxContacts);
	m_calculateIterations = (0 == iterations);
}


void ParticleWorld::Update(float deltaTime)
{
	m_registry.Update(deltaTime);

	integrate(deltaTime);

	unsigned int usedContacts = generateContacts();

	if (usedContacts)
	{
		if (m_calculateIterations) m_resolver.SetIterations(usedContacts * 2);
		m_resolver.Update(m_particleContacts, deltaTime);
	}	
}


void ParticleWorld::integrate(float deltaTime)
{
	for (int p = 0; p < m_particles.size(); ++p)
	{
		m_particles[p]->Update(deltaTime);
	}
}


unsigned int ParticleWorld::generateContacts()
{
	int limit = m_maxContacts;
	unsigned int contactIndex = 0;

	for (int c = 0; c < m_particleConnstraints.size() && (limit > 0); ++c)
	{
		unsigned int used = m_particleConnstraints[c]->AddContact(m_particleContacts[contactIndex]);
		limit -= used;
		contactIndex += used;
	}

	return m_maxContacts - limit;
}

void ParticleWorld::ClearFrame()
{
	for (int p = 0; p < m_particles.size(); ++p)
	{
		m_particles[p]->ClearForces();
	}
}