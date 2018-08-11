#include "ParticleContact.h"


using namespace FME::Simulation;


ParticleContact::ParticleContact()
{
	m_particles = std::vector<std::shared_ptr<Particle>>(2);
}


void ParticleContact::Update(float deltaTime)
{
	resolveVelocity(deltaTime);
	resolveInterpenetration(deltaTime);
}


void ParticleContact::resolveInterpenetration(float deltaTime)
{
	float totalInverseMass = m_particles[0]->GetInverseMass();

	if (m_particles[1])
	{
		totalInverseMass = totalInverseMass + m_particles[1]->GetInverseMass();
	}
	if ((m_penetration > 0.0f) && (totalInverseMass > 0.0f))
	{
		glm::vec3 movementPerMass = m_contactNormal * (m_penetration / totalInverseMass);
		glm::vec3 movement0 = m_particles[0]->GetInverseMass() * movementPerMass;
		m_particles[0]->SetPosition(m_particles[0]->GetPosition() + movement0);

		if (m_particles[1])
		{
			glm::vec3 movement1 = -m_particles[1]->GetInverseMass() * movementPerMass;
			m_particles[1]->SetPosition(m_particles[1]->GetPosition() + movement1);
		}
	}
}


float ParticleContact::CalculateSeparatingVelocity() const
{
	glm::vec3 relativeVelocity = m_particles[0]->GetVelocity();

	if (m_particles[1])
	{
		relativeVelocity = relativeVelocity - m_particles[1]->GetVelocity();
	}

	return glm::dot(m_contactNormal, relativeVelocity);
}


void ParticleContact::resolveVelocity(float deltaTime)
{
	float separatingVelocity = CalculateSeparatingVelocity();
	float totalInverseMass = m_particles[0]->GetInverseMass();

	if (m_particles[1])
	{
		totalInverseMass = totalInverseMass + m_particles[1]->GetInverseMass();
	}


	if ((separatingVelocity <= 0.0f) && (totalInverseMass > 0.0f))
	{
		float newSeparatingVelocity = -separatingVelocity * m_restitution;

		glm::vec3 accCausedVelocity = m_particles[0]->GetAcceleration();
		if (m_particles[1])
		{
			accCausedVelocity = accCausedVelocity - m_particles[1]->GetAcceleration();
		}
		float accCausedSepVelocity = glm::dot(accCausedVelocity, m_contactNormal) * deltaTime;
		if (accCausedSepVelocity < 0.0f)
		{
			newSeparatingVelocity = newSeparatingVelocity + m_restitution * accCausedSepVelocity;
			if (newSeparatingVelocity < 0.0f) newSeparatingVelocity = 0.0f;
		}

		float deltaVelocity = newSeparatingVelocity - separatingVelocity;

		float impulse = deltaVelocity / totalInverseMass;
		glm::vec3 impulseVector = impulse * m_contactNormal;

		m_particles[0]->SetVelocity(m_particles[0]->GetVelocity() + impulseVector * m_particles[0]->GetInverseMass());
		if (m_particles[1])
		{
			m_particles[1]->SetVelocity(m_particles[1]->GetVelocity() - impulseVector * m_particles[1]->GetInverseMass());
		}
	}
}
