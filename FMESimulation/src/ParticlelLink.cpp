#include "ParticleLink.h"

using namespace FME::Simulation;


ParticleLink::ParticleLink()
{
	m_particles = std::vector<std::shared_ptr<Particle>>(2);
}



float ParticleLink::getCurrentLinkLength() const
{
	glm::vec3 diffPos = m_particles[0]->GetPosition() - m_particles[1]->GetPosition();

	return glm::length(diffPos);
}

glm::vec3 ParticleLink::getContactNormal() const
{
	glm::vec3 normal = m_particles[1]->GetPosition() - m_particles[0]->GetPosition();

	return glm::normalize(normal);
}
