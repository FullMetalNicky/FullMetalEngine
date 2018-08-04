#include "ParticleGravity.h"

using namespace FME::Simulation;


ParticleGravity::ParticleGravity(const glm::vec3& gravity)
{
	m_gravity = gravity;
}


void ParticleGravity::Update(std::shared_ptr<Particle> particle, float deltaTime)
{
	if (particle->GetInverseMass() <= 0.0f) return;

	particle->AddForce(m_gravity * particle->GetMass());
}