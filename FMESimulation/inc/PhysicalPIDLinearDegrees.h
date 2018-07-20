#include "IPhysicalForce.h"
#include "PhysicalModel.h"

/** \class PhysicalPIDLinearDegrees
*  \brief Inherits from IPhysicalForce interface. A PD controller for camera position.
*/
namespace FME
{
	namespace Simulation
	{
		class PhysicalPIDLinearDegrees : public IPhysicalForce
		{
		public:

			/** \brief PhysicalPIDOrientation
			* \details a constructor.
			*
			* \param initialPos glm::vec3  initial position of the camera
			* \param degrees float degrees to rotates the camera by
			* \param springConstant float spring coefficiant for PD equation
			* \param dumpingFactor float dumping factor for PD equation
			*
			* \return void
			*/

			PhysicalPIDLinearDegrees(glm::vec3 initialPos, float degrees, float springConstant, float dumpingFactor = 1.0f);

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



			glm::vec3 m_initialPos;
			float m_initialDegrees;
			float m_degrees;
			float m_springConstant;
			float m_dumpingFactor;
		};
	}
}