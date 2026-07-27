#pragma once

#include <core/engine_context.h>
#include <core/rendering/vertex_array.h>
#include <core/windowing/window.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ref_scope.h>

#include <iostream>
#include <memory>
#include <vector>

#include "application.h"
#include "console.h"
#include "core/logging/debug.h"
#include "editor_context.h"
#include "game_player.h"
#include "hierarchy.h"
#include "inspector.h"
#include "panel.h"
#include "platform/api.h"
#include "project_window.h"
#include "theme.h"
#include "viewport.h"

#ifdef _WIN32
#include "platform/windows/win32.h"
#elif __linux__
#include "platform/linux/linux.h"
#endif

// ImGui is the default editor library
#define POTATO_EDITOR_USE_IMGUI

namespace PotatoEngine::Editor {

class EditorApplication : public Core::Application {
private:
    std::unique_ptr<Core::Windowing::Window> m_window;

    Platform::PlatformAPI* m_platform = nullptr;

    EditorContext m_editorContext;
    Core::EngineContext m_engineContext;
    std::vector<std::unique_ptr<EditorPanel>> m_panels;

public:
private:
    void menuBar() const;

public:
    EditorApplication();
    ~EditorApplication();

public:
    void OnStart() override;
    void OnUpdate() override;
    void OnDestroy() override;

public:
    bool ShouldClose() const;
    void SetPlatform(Platform::PlatformAPI* p) { m_platform = p; }

    template <typename T, typename... Args>
    T* AddPanel(Args&&... args) {
        static_assert(std::is_base_of_v<EditorPanel, T>,
                      "T must derive from EditorPanel");

        auto panel = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = panel.get();
        m_panels.push_back(std::move(panel));
        return ptr;
    }
};
};  // namespace PotatoEngine::Editor
