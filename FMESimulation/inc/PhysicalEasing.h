#include "IPhysicalForce.h"
#include "PhysicalModel.h"
#include <functional>

/** \class PhysicalEasing
*  \brief Inherits from IPhysicalForce interface. A PD controller for camera position.
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalEasing : public IPhysicalForce
		{
		public:

			/** \brief PhysicalEaseOut
			* \details a constructor.
			*
			* \param initialPos glm::vec3  initial position of the camera
			* \param endPos glm::vec3  end position of the camera
			* \param duration float duration for motion
			*
			* \return void
			*/

			PhysicalEasing(glm::vec3 endPos, float duration, bool linear, float(*easingFunc)(float) = nullptr);

			/** \brief getForces
			* \details This function calculates the forces.
			*
			* \param physicalModel const PhysicalModel*  physicalModel element
			* \param deltaTime float the time difference since the last calculation
			*
			* \return glm::vec3  the forces acting on the object on each axis
			*/

			virtual glm::vec3 getForces(const PhysicalModel* physicalModel, float deltaTime) const override;

		private:

			std::function<float(float)> m_easing;
			bool m_linear;
			glm::vec3 m_endPos;
			float m_duration;
			glm::vec3 m_deltaPos;
			mutable float m_currentTime;
		};
	}
}