#ifndef CAMERA_H_
#define CAMERA_H_

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace FME
{
	namespace Graphics
	{
		/** \class Camera
		*  \brief A class that implements a default/simple camera in 3D, allowing for basic motion like zoom, tumble and pan
		*/

		class Camera
		{
			public:
				Camera(const glm::vec3& camPosition, const glm::vec3& camPOI);

				void Update();

				void PanTumble(float xOffset, float yOffset);
				void Zoom(float zOffset);
				void Translate(float xOffset, float zOffset);
				void Rotate(float xOffset, float zOffset);
				void Elevate(float yOffset);				

				void SetPosition(const glm::vec3& position) { m_camPos = position; };
				void SetPOI(const glm::vec3& POI) { m_camPOI = POI; };
				void ResetCamera();

				glm::mat4 GetViewMatrix() const { return m_view; };

			private:

				glm::vec3 m_camPos;
				glm::vec3 m_camResetPos;
				glm::vec3 m_camPOI;
				glm::vec3 m_camResetPOI;
				glm::vec3 m_upVec;

				glm::mat4 m_view;
				float m_zoom;

		};
	}
}

#endif