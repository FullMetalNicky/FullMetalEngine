#include "ParticleSpring.h"


using namespace FME::Simulation;


ParticleSpring::ParticleSpring(std::shared_ptr<Particle> otherParticle, float coeff, float restLength)
{
	m_otherParticle = otherParticle;
	m_coeff = coeff;
	m_restLength = restLength;
}


void ParticleSpring::Update(std::shared_ptr<Particle> particle, float deltaTime)
{
	glm::vec3 pos = particle->GetPosition();
	glm::vec3 otherPos = m_otherParticle->GetPosition();

	float distance = glm::length(pos - otherPos);
	float magnitude = abs(distance - m_restLength) * m_coeff;

	glm::vec3 force = -magnitude * glm::normalize(pos - otherPos);
	particle->AddForce(force);
}