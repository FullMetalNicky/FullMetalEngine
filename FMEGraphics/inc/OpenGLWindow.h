#ifndef OPENGLWINDOW_H_
#define OPENGLWINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

namespace FME
{
	namespace Graphics
	{
		/** \class OpenGLWindow
		*  \brief A class implementing an OpenGL app. It initiates the context for GLEW and GLFW and handles the windowing.
		*/

		class OpenGLWindow
		{
		public:
			OpenGLWindow(glm::ivec2 windowSize, glm::ivec2 version, const std::string& windowName, bool renderFullScreen = false);
			virtual ~OpenGLWindow();

			void Update();
			void Draw();
			bool Alive() { return !glfwWindowShouldClose(m_window); };

			GLFWwindow* GetWindow() const { return m_window;};
			void SetKeyboardCallback(GLFWkeyfun key_callback);
			void SetCursorCallback(GLFWcursorposfun cursor_callback);

		private:

			GLFWwindow* m_window;
		};

	}
}
#endif

