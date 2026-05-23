// Central editor class.

#ifndef POTATO_EDITOR_H
#define POTATO_EDITOR_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "application.h"
#include "platform/api.h"

#include "panel.h"
#include "viewport.h"

#include <iostream>
#include <vector>

#ifdef _WIN32
#include "platform/windows/win32.h"
#endif

// ImGui is the default editor library
#define POTATO_EDITOR_USE_IMGUI true

using namespace PotatoEngine::Platform;

namespace PotatoEngine::Editor {

	class EditorApplication : public Core::Application {
	private:
		GLFWwindow  *m_glfwWindow = nullptr;
		PlatformAPI *m_platform = nullptr;

		std::vector<EditorPanel*> panels;

	private:
		void menuBar() const;

	public:
		 EditorApplication();
		~EditorApplication();

	public:
		void OnStart()   override;
		void OnUpdate()  override;
		void OnDestroy() override;

	public:
		bool ShouldClose() const;
		void SetPlatform(PlatformAPI* p) { m_platform = p; }
		
		void AddPanel(EditorPanel* panel) { panels.push_back(panel); }
	};
};


#endif // POTATO_EDITOR_H