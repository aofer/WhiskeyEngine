#include "InputManager.h"
#include <glm/glm.hpp>
#include <GLFW\glfw3.h>
using namespace Managers;



void InputManager::update(float dt)
{

}

void InputManager::AddInputListener(Core::IInputListener* listener)
{
	m_inputListeners.push_back(listener);
}

void InputManager::onKeyboardEvent(int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		for (auto iter = m_inputListeners.begin(); iter != m_inputListeners.end(); iter++)
		{
			(*iter)->onKeyPressed(key, scancode);
		}
	}
	else if (action == GLFW_RELEASE)
	{
		for (auto iter = m_inputListeners.begin(); iter != m_inputListeners.end(); iter++)
		{
			(*iter)->onKeyReleased(key, scancode);
		}
	}

}