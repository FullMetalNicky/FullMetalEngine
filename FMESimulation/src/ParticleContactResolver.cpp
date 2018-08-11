#include "ParticleContactResolver.h"

using namespace FME::Simulation;


ParticleContactResolver::ParticleContactResolver(unsigned int iterations)
{
	m_iterations = iterations;
}


void ParticleContactResolver::SetIterations(unsigned int iterations)
{
	m_iterations = iterations;
}


void ParticleContactResolver::Update(const std::vector<std::shared_ptr<ParticleContact>>& particleContacts, float deltaTime)
{
	for (unsigned int iter = 0; iter < m_iterations; ++iter)
	{
		unsigned int index = findMostSevereContact(particleContacts);
		if (particleContacts.size() == index) break;

		particleContacts[index]->Update(deltaTime);
	}
}

unsigned int ParticleContactResolver::findMostSevereContact(const std::vector<std::shared_ptr<ParticleContact>>& particleContacts)
{
	unsigned int index = particleContacts.size();

	float maxVal = FLT_MAX;
	for (int pc = 0; pc < particleContacts.size(); ++pc)
	{
		float separatingVelocity = particleContacts[pc]->CalculateSeparatingVelocity();
		if ((separatingVelocity < maxVal) && ((separatingVelocity < 0.0f) || (particleContacts[pc]->GetPenetration() > 0.0f)))
		{
			maxVal = separatingVelocity;
			index = pc;
		}
	}

	return index;
}

