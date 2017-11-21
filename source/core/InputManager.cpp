#include "core\InputManager.h"

namespace engine {

	InputManager::InputManager() : m_mouseX(0.0f), m_mouseY(0.0f)
	{
		
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::setMouseCoords(float x, float y) {
		m_mouseX = x;
		m_mouseY = y;
	}

	float InputManager::getMouseX() {
		return m_mouseX;
	}

	float InputManager::getMouseY() {
		return m_mouseY;
	}
}