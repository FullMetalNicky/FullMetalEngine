#include "IPhysicalForce.h"
#include "PhysicalModel.h"

/** \class PhysicalPIDPosition
*  \brief Inherits from IPhysicalForce interface. A PD controller for camera position.
*/
namespace FME
{
	namespace Simulation
	{

		class PhysicalPIDPosition : public IPhysicalForce
		{
		public:

			/** \brief PhysicalPIDPosition
			* \details a constructor.
			*
			* \param targetPos glm::vec3  desired position of the camera
			* \param springConstant float spring coefficiant for PD equation
			* \param dumpingFactor float dumping factor for PD equation
			*
			* \return void
			*/

			PhysicalPIDPosition(glm::vec3 targetPos, float springConstant, float dumpingFactor = 1.0f);

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
			glm::vec3 m_target;
			float m_springConstant;
			float m_dumpingFactor;
		};
	}
}