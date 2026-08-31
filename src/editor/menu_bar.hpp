#pragma once

#include <core/engine_context.h>
#include <imgui/imgui.h>

#include "editor_context.h"

namespace PotatoEngine::Editor {

class MenuBar {
private:
    EditorContext& m_editorContext;
    Core::EngineContext& m_engineContext;

    std::queue<std::function<void()>> m_events;

private:
    void File();
    void Edit();
    void View();
    void Help();

public:
    MenuBar(EditorContext& editor, Core::EngineContext& engine)
        : m_editorContext(editor), m_engineContext(engine) {}

    ~MenuBar() = default;

public:
    void Render();

    // This should be called at the end of frame so the engine don't freezes
    // with save/open actions
    void ExecEvents();
};

}  // namespace PotatoEngine::Editor
