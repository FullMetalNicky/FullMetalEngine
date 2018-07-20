#pragma once

#include <chrono>
#include <vector>
#include "PhysicalModel.h"
#include "IPhysicalTrajectory.h"



/** \class PhysicalSimulation
*  \brief This class runs the engine.
*  \details It recieves data about the object's current position, velocity, etc. and determines the object's properties by calculating the forces acting on it.
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalSimulation
		{
		public:


			PhysicalSimulation(float maxDeltaTime = 0.05f);

			/** \brief addSubject
			* \details adds a subject to a list of elements that are effected by the physical simulation.
			*
			* \param subject PhysicalModel*
			*
			* \return void
			*/

			void addSubject(PhysicalModel* subject);

			/** \brief calculate
			* \details calculates the forces applied on each subject in the list and updates their next state.
			*
			* \param deltaTime float time interval since last simulation
			*
			* \return void
			*/

			void Update(float deltaTime);

			long long getRealTime();
			float getSimulationTime();


		private:

			void UpdateOnce(float deltaTime);
			std::vector<PhysicalModel*> m_subjects;
			float m_maxTimeStep;
			float m_simulationTime = 0.0f;
			float m_accumulator = 0.0f;
			std::chrono::high_resolution_clock::time_point m_startTime;
		};
	}
}