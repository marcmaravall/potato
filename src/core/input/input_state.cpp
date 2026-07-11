#include "input_state.h"

namespace PotatoEngine::Core::Input {
	bool InputState::IsKey(Key key) {
		return m_keyboardCurrent[(size_t)key];
	}

	bool InputState::IsKeyDown(Key key) {
		return m_keyboardCurrent[(size_t)key] && !m_keyboardLast[(size_t)key];
	}

	bool InputState::IsKeyUp(Key key) {
		return !m_keyboardCurrent[(size_t)key] && m_keyboardLast[(size_t)key];
	}

	bool InputState::IsMouseButton(MouseButton button) {
		return m_mouseCurrent[(size_t)button];
	}

	bool InputState::IsMouseButtonDown(MouseButton button) {
		return m_mouseCurrent[(size_t)button] && !m_mouseLast[(size_t)button];
	}
	
	bool InputState::IsMouseButtonUp(MouseButton button) {
		return m_mouseLast[(size_t)button] && !m_mouseCurrent[(size_t)button];
	}

	InputState::InputState(GLFWwindow* window) : m_window(window) {
		glfwSetKeyCallback(window, 
			[](GLFWwindow* window, int key, int scancode, int action, int mods) {
				// TODO: map glfw keys to Key enum
				MEB_LOG("Pressed a key!");
			}
		);

		glfwSetMouseButtonCallback(window,
			[](GLFWwindow* window, int button, int action, int mods) {
				
			}
		);
	}

	void InputState::Update() {
		MEB_ASSERT(m_mouseCurrent.size() == m_mouseLast.size() && "ERROR: mouse sizes are different!");
		MEB_ASSERT(m_keyboardCurrent.size() == m_keyboardLast.size() && "ERROR: keyboard sizes are different!");
		
		for (size_t i = 0; i < m_keyboardCurrent.size(); i++) {
			m_keyboardLast[i] = m_keyboardCurrent[i];
			m_keyboardCurrent[i] = false;
		}
		
		for (size_t i = 0; i < m_mouseCurrent.size(); i++) {
			m_mouseLast[i] = m_mouseCurrent[i];
			m_mouseCurrent[i] = false;
		}
	}
}
