#include "InputManager.h"

using namespace FME::Graphics;

void defaultKeyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mode);
void defaultMouseCallbackWrapper(GLFWwindow* window, double xpos, double ypos);

std::shared_ptr<InputManager> InputManager::m_instance = nullptr;

std::shared_ptr<InputManager> InputManager::Instance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<InputManager>(new InputManager());
	}
	return m_instance;
}


void InputManager::SetWindow(glm::ivec2 windowSize, GLFWwindow* window)
{
	m_lastX = windowSize.x / 2;
	m_lastY = windowSize.y / 2;
	m_window = window;

	glfwSetKeyCallback(m_window, defaultKeyCallbackWrapper);
	glfwSetCursorPosCallback(m_window, defaultMouseCallbackWrapper);
}


InputManager::InputManager()
{
	m_keys = std::vector<bool>(1024, false);
}


void InputManager::defaultKeyCallback(int key, int scancode, int action, int mode)
{

	if (action == GLFW_PRESS)
		m_keys[key] = true;
	else if (action == GLFW_RELEASE)
		m_keys[key] = false;

}


void InputManager::defaultMouseCallback(double xpos, double ypos)
{
	if (m_firstMouse)
	{
		m_lastX = xpos;
		m_lastY = ypos;
		m_firstMouse = false;
	}

	double xoffset = xpos - m_lastX;
	double yoffset = m_lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	m_lastX = xpos;
	m_lastY = ypos;
}


void defaultKeyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	InputManager::Instance()->defaultKeyCallback(key, scancode, action, mode);
}


void defaultMouseCallbackWrapper(GLFWwindow* window, double xpos, double ypos)
{
	InputManager::Instance()->defaultMouseCallback(xpos, ypos);
}


void InputManager::Update()
{
	glfwPollEvents();
}