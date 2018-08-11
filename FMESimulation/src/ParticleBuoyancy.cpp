#include "ParticleBuoyancy.h"


using namespace FME::Simulation;


ParticleBuoyancy::ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity)
{
	m_maxDepth = maxDepth;
	m_volume = volume;
	m_waterHeight = waterHeight;
	m_liquidDensity = liquidDensity;
}


void ParticleBuoyancy::Update(std::shared_ptr<Particle> particle, float deltaTime)
{
	float depth = particle->GetPosition().y;

	if (depth >= m_waterHeight + m_maxDepth) return;

	glm::vec3 force(0.0f);
	if (depth <= m_waterHeight - m_maxDepth)
	{
		force.y = m_liquidDensity * m_volume;
	}
	else
	{
		force.y = m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / (2.0 * m_maxDepth);
	}

	particle->AddForce(force);
}