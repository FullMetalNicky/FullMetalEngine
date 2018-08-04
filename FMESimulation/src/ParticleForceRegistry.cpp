#include "ParticleForceRegistry.h"

using namespace FME::Simulation;


void ParticleForceRegistry::Update(float deltaTime)
{
	for (int i = 0; i < m_registrations.size(); ++i)
	{
		m_registrations[i].particleForce->Update(m_registrations[i].particle, deltaTime);
	}
}


void ParticleForceRegistry::Clear()
{
	m_registrations.clear();
}


void ParticleForceRegistry::Add(std::shared_ptr<Particle> particle, std::shared_ptr<IParticleForce> particleForce)
{
	m_registrations.push_back(ParticleForceRegistration{ particle , particleForce });
}


void ParticleForceRegistry::Remove(std::shared_ptr<Particle> particle, std::shared_ptr<IParticleForce> particleForce)
{
	//not sure if should implement 

}