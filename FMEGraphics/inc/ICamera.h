#ifndef ICAMERA_H_
#define ICAMERA_H_

#include <glm/glm.hpp>

namespace FME
{
	namespace Graphics
	{
		/** \class ICamera
		*  \brief general interface for a camera, including the must-have's for rendering
		*/

		class ICamera
		{
			public:

				virtual ~ICamera() {};
				
				void SetProjectionMatrix(glm::mat4 proj) { m_proj = proj; };
				void SetViewMatrix(glm::mat4 view) { m_view = view; };

				glm::mat4 GetProjectionMatrix() const { return m_proj; };
				glm::mat4 GetViewMatrix() const { return m_view; };

			protected:
				glm::mat4 m_view;
				glm::mat4 m_proj;			
		};
	}
}

#endif