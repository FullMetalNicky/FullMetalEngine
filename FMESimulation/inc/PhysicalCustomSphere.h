#pragma once
#include "IPhysicalTrajectory.h"

namespace FME
{
	namespace Simulation
	{
		class PhysicalCustomSphere : public IPhysicalTrajectory
		{
		public:
			/*
			Parameters:
			Recieves a float defining the sensitivity, which determines how great is effect of the input on the movement,
			a vec2 (minimum angle, ,maximum angle) which the defines the sphere's cutoff angles relative to the y axis.
			and a vec2 (minimum radius, ,maximum radius) which the defines how close/far can you be to the sphere's center.
			*/

			PhysicalCustomSphere(float sensitivity = 0.05f, glm::vec2 cutoffAngles = glm::vec2(0.0f, 180.f), glm::vec2 radiusRange = glm::vec2(0.0f, HUGE_VALF));

			/*
			Parameters:
			Recieves a vec3 with the object's change in position, a vec3 with the object's previous position and vec3
			describing the POI which is relevant for spherical surfaces.
			Return value:
			Vec3 with the next position of the object
			*/

			virtual glm::vec3 calculateTrajectory(glm::vec3 deltaPos, glm::vec3 currPos, glm::vec3 POI = glm::vec3(0.0f, 0.0f, 0.0f)) override;

		private:
			float m_sensitivity;
			glm::vec2 m_cutoffAngles;
			glm::vec2 m_radiusRange;
		};
	}
}