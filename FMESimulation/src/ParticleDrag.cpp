#include "ParticleDrag.h"

using namespace FME::Simulation;


ParticleDrag::ParticleDrag(const glm::vec2& kCoeffs)
{
	m_kCoeffs = kCoeffs;
}


void ParticleDrag::Update(std::shared_ptr<Particle> particle, float deltaTime)
{
	//if (particle->GetInverseMass() <= 0.0f) return;

	glm::vec3 vel = particle->GetVelocity();
	float velMag = glm::length(vel);
	float drag = m_kCoeffs.x  * velMag + m_kCoeffs.y * powf(velMag, 2.0);
	glm::vec3 force = -drag * glm::normalize(vel);

	particle->AddForce(force);
}