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
#include "context.h"
#include "viewport.h"
#include "console.h"
#include "inspector.h"

#include "core/logging/debug_system.h"
#include "theme.h"

#include <iostream>
#include <vector>
#include <memory>

#ifdef _WIN32
#include "platform/windows/win32.h"
#endif

// ImGui is the default editor library
#define POTATO_EDITOR_USE_IMGUI true

namespace PotatoEngine::Editor {

	class EditorApplication : public Core::Application {
	private:
		GLFWwindow  *m_glfwWindow = nullptr;
		Platform::PlatformAPI *m_platform = nullptr;

		std::vector<std::unique_ptr<EditorPanel>> m_panels;

	public:
		EditorContext m_context;

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
		void SetPlatform(Platform::PlatformAPI* p) { m_platform = p; }

		template<typename T, typename... Args>
        T* AddPanel(Args&&... args) {
            static_assert(std::is_base_of_v<EditorPanel, T>,
                "T must derive from EditorPanel");

            auto panel = std::make_unique<T>(std::forward<Args>(args)...);
            T* ptr = panel.get();
            m_panels.push_back(std::move(panel));
            return ptr;
        }
	};
};


#endif // POTATO_EDITOR_H