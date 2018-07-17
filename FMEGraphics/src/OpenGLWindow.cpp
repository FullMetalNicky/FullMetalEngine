#include "OpenGLWindow.h"

using namespace FME::Graphics;


OpenGLWindow::OpenGLWindow(glm::ivec2 windowSize, glm::ivec2 version, const std::string& windowName, bool renderFullScreen)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version.x);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version.y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (renderFullScreen)
	{
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		GLFWmonitor* primary = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primary);
		m_window = glfwCreateWindow(windowSize.x, windowSize.y, windowName.c_str(), primary, NULL); // Windowed
        glfwSetWindowMonitor(m_window, primary, 0, 0, windowSize.x, windowSize.y, mode->refreshRate);
	}
	else
	{
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		m_window = glfwCreateWindow(windowSize.x, windowSize.y, windowName.c_str(), NULL, NULL); // Windowed
	}

	glfwMakeContextCurrent(m_window);
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, 1);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glewExperimental = GL_TRUE;
	glewInit();
	glViewport(0, 0, windowSize.x, windowSize.y);
	glEnable(GL_DEPTH_TEST);
}


void OpenGLWindow::SetKeyboardCallback(GLFWkeyfun key_callback)
{
	glfwSetKeyCallback(m_window, key_callback);
}


void OpenGLWindow::SetCursorCallback(GLFWcursorposfun cursor_callback)
{
	glfwSetCursorPosCallback(m_window, cursor_callback);
}


void OpenGLWindow::Update()
{	
	glfwPollEvents();	
}

void OpenGLWindow::Draw()
{
	glfwSwapBuffers(m_window);
}


OpenGLWindow::~OpenGLWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
