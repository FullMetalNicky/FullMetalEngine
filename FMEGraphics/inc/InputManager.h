#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace FME
{
	namespace Graphics
	{
		/** \class InputManager
		*  \brief A singleton class handling the user input and providing the other engine entities with access to it.
		*/

		class InputManager
		{
		public:

			static std::shared_ptr<InputManager> Instance();

			void SetWindow(glm::ivec2 windowSize, GLFWwindow* window);

			void Update();	

			void defaultKeyCallback(int key, int scancode, int action, int mode);

			void defaultMouseCallback(double xpos, double ypos);

			std::vector<bool> GetKeys() const { return m_keys; };

		protected:

			InputManager();

		private:

			
			static std::shared_ptr<InputManager> m_instance;
			GLFWwindow* m_window;
			std::vector<bool> m_keys;
			bool m_firstMouse = true;
			double m_lastX;
			double m_lastY;
		};
	}
}

#endif
