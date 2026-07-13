#pragma once

#include <string>

#include <meb.h>
#include <core/windowing/window.h>

#include <GLFW/glfw3.h>

namespace PotatoEngine::Core::Windowing {

	class GLFW_WindowBackend : public Window {
	private:
		GLFWwindow* m_glfwWindow = nullptr;
		Input::InputState* m_inputStatePtr;

		static constexpr int k_trackedGlfwKeys[] = {
			GLFW_KEY_Q, GLFW_KEY_W, GLFW_KEY_E, GLFW_KEY_R, GLFW_KEY_T, GLFW_KEY_Y,
			GLFW_KEY_U, GLFW_KEY_I, GLFW_KEY_O, GLFW_KEY_P, GLFW_KEY_A, GLFW_KEY_S,
			GLFW_KEY_D, GLFW_KEY_F, GLFW_KEY_G, GLFW_KEY_H, GLFW_KEY_J, GLFW_KEY_K,
			GLFW_KEY_L, GLFW_KEY_Z, GLFW_KEY_X, GLFW_KEY_C, GLFW_KEY_V, GLFW_KEY_B,
			GLFW_KEY_N, GLFW_KEY_M,
			GLFW_KEY_LEFT_CONTROL, GLFW_KEY_RIGHT_CONTROL,
			GLFW_KEY_LEFT_SHIFT, GLFW_KEY_RIGHT_SHIFT,
			GLFW_KEY_CAPS_LOCK,
			GLFW_KEY_LEFT_ALT, GLFW_KEY_RIGHT_ALT,
			GLFW_KEY_TAB, GLFW_KEY_ESCAPE, GLFW_KEY_SPACE, GLFW_KEY_ENTER, GLFW_KEY_KP_ENTER,
			GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3, GLFW_KEY_4, GLFW_KEY_5,
			GLFW_KEY_6, GLFW_KEY_7, GLFW_KEY_8, GLFW_KEY_9, GLFW_KEY_0,
			GLFW_KEY_F1, GLFW_KEY_F2, GLFW_KEY_F3, GLFW_KEY_F4, GLFW_KEY_F5, GLFW_KEY_F6,
			GLFW_KEY_F7, GLFW_KEY_F8, GLFW_KEY_F9, GLFW_KEY_F10, GLFW_KEY_F11, GLFW_KEY_F12,
			GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN
		};

	public:
		Input::Key ToInputKey(int glfwKey);
	
	public:
		GLFW_WindowBackend(const std::string& title, size_t width, size_t height, void* share = nullptr);
		~GLFW_WindowBackend();

	public:

		virtual void MakeContextCurrent() override { glfwMakeContextCurrent(m_glfwWindow); }
		virtual void PollEvents(Input::InputState& state) override;
		virtual bool ShouldClose() override { return glfwWindowShouldClose(m_glfwWindow); }
		void SwapBuffers() override;

	public:
		void* GetData() override { return m_glfwWindow; }
	
	public: 
		static void Init();
	};
}
