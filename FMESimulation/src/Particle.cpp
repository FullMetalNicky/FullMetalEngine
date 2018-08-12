#include "Particle.h"

using namespace FME::Simulation;



void Particle::Update(float deltaTime)
{
	if (m_inverseMass <= 0.0f) return;

	//assert(duration > 0.0);

	m_position = m_position + m_velocity * deltaTime; //acceleration neglected because deltaTime^2 is really small and insignificant but heavy in compute

	m_acceleration = m_forceAccumulator * m_inverseMass;
	m_velocity = m_velocity + m_acceleration * deltaTime;
	m_velocity = m_velocity * powf(m_dumping, deltaTime);

	//ClearForces()?
	//m_forceAccumulator = glm::vec3(0.0f);
}

void Particle::ClearForces()
{
	m_forceAccumulator = glm::vec3(0.0f);
}

void Particle::AddForce(const glm::vec3& force)
{
	m_forceAccumulator = m_forceAccumulator + force;
}

float Particle::GetMass() const
{
	if (m_inverseMass > 0.0f) return 1.0f / m_inverseMass;
	else return LLONG_MAX;
}