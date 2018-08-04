#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "glm\glm.hpp"

namespace FME
{
	namespace Simulation
	{
		class Particle
		{
		public:

			void Update(float deltaTime);

			void AddForce(const glm::vec3& force);

			void SetInverseMass(float inverseMass) { m_inverseMass = inverseMass; };
			void SetMass(float mass) { m_inverseMass = 1.0f / mass; };
			void SetPosition(const glm::vec3& position) { m_position = position; };
			void SetVelocity(const glm::vec3& velocity) { m_velocity = velocity; };
			void SetAcceleration(const glm::vec3& acceleration) { m_acceleration = acceleration; };
			void SetDumping(float dumping) { m_dumping = dumping; };


			float GetMass() const;
			float GetInverseMass() const { return m_inverseMass; };
			glm::vec3 GetPosition() const { return m_position; };
			glm::vec3 GetVelocity() const { return m_velocity; };
			glm::vec3 GetAcceleration() const { return m_acceleration; };
			float GetDumping() const { return m_dumping; };


		protected:

			glm::vec3 m_position;
			glm::vec3 m_velocity;
			glm::vec3 m_acceleration;
			glm::vec3 m_forceAccumulator = glm::vec3(0.0f);
			float m_dumping = 0.999f;
			float m_inverseMass = 0.0f;
		}; 
	}
}

#endif
