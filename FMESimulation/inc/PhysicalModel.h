#pragma once

#include <memory>
#include <vector>
#include <map>
#include "IPhysicalForce.h"
#include "IPhysicalTrajectory.h"


/** \class PhysicalModel
*  \brief A physical Subject.
*  \details wrapper for the subject's attributes/properties and the forces operating on it
*/

namespace FME
{
	namespace Simulation
	{
		class PhysicalModel
		{
		public:
			PhysicalModel(glm::vec3 position, glm::vec3 POI, float mass, float inertia);
			void addLinearForce(std::string forcaName, std::shared_ptr<IPhysicalForce> force);
			void addAngularForce(std::string forcaName, std::shared_ptr<IPhysicalForce> force);
			void removeLinearForce(std::string forcaName);
			void removeAngularForce(std::string forcaName);
			void removesAllForces();
			std::map<std::string, std::shared_ptr<IPhysicalForce>>const getLinearForces() const;
			std::map<std::string, std::shared_ptr<IPhysicalForce>>const getAngularForces() const;
			void setPosition(glm::vec3 Position);
			void setDeltaPosition(glm::vec3 deltaPosition);
			void setDeltaPOI(glm::vec3 deltaPOI);
			void setLastVelocity(glm::vec3 velocity);
			void setLastAngularVelocity(glm::vec3 velocity);
			void setPOI(glm::vec3 POI);

			glm::vec3 getPosition() const;
			float getMass()const;
			float getInertia()const;
			glm::vec3 getLastVelocity() const;
			glm::vec3 getLastAngularVelocity() const;
			glm::vec3 const& getPOI() const;
			glm::vec3 const& getDeltaPosition()const;
			glm::vec3 const& getDeltaPOI()const;
			void setLinearTrajectory(std::shared_ptr<IPhysicalTrajectory> trajectory);
			std::shared_ptr<IPhysicalTrajectory> getLinearTrajectory()const;
			void setAngularTrajectory(std::shared_ptr<IPhysicalTrajectory> trajectory);
			std::shared_ptr<IPhysicalTrajectory> getAngularTrajectory()const;
			glm::vec3 calculateAngularTrajectory(glm::vec3 deltaPos);
			glm::vec3 calculateLinearTrajectory(glm::vec3 deltaPos);

		private:

			std::map<std::string, std::shared_ptr<IPhysicalForce>>m_linearForces;
			std::map<std::string, std::shared_ptr<IPhysicalForce>>m_angularForces;
			std::shared_ptr<IPhysicalTrajectory> m_linearTrajectory = nullptr;
			std::shared_ptr<IPhysicalTrajectory> m_angularTrajectory = nullptr;
			glm::vec3 m_position;
			glm::vec3 m_POI;
			float m_mass;
			float m_inertia;
			glm::vec3 m_deltaPosition;
			glm::vec3 m_deltaPOI;
			glm::vec3 m_lastVelocity;
			glm::vec3 m_lastAngularVelocity;

		};
	}
}