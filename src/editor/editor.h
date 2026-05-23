// Central editor class.

#ifndef POTATO_EDITOR_H
#define POTATO_EDITOR_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

// ImGui is the default editor library
#define POTATO_EDITOR_USE_IMGUI true

namespace PotatoEngine {

	class Editor {
	private:
		GLFWwindow *m_glfwWindow = nullptr;

	public:
		 Editor();
		~Editor();

	public:
		int  Init();
		
		void Update();
		void End();

	public:
		bool ShouldClose() const;
	};
};


#endif // POTATO_EDITOR_H