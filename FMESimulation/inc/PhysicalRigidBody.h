#pragma once

#include <vector>
#include <glm/glm.hpp>

/*
	This class holds the object's attributes and properties.
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalRigidBody
		{
		public:
			PhysicalRigidBody(glm::vec3 position, float mass);
			void updatePosition(glm::vec3 position);
			void updateDeltaPosition(glm::vec3 deltaPosition);
			void updateLastVelocity(glm::vec3 velocity);
			void updatePOI(glm::vec3 POI);
			glm::vec3 const& getPosition() const;
			glm::vec3 const& getDeltaPosition()const;
			float const& getMass()const;
			glm::vec3 const& getLastVelocity() const;
			glm::vec3 const& getPOI() const;

		private:
			glm::vec3 m_position;
			glm::vec3 m_deltaPosition;
			float m_mass;
			glm::vec3 m_lastVelocity;
			glm::vec3 m_POI;
		};
	}
}