#pragma once

#include <core/engine_context.h>
#include <imgui/imgui.h>

#include "editor_context.h"

namespace PotatoEngine::Editor {

class MenuBar {
private:
    EditorContext& m_editorContext;
    Core::EngineContext& m_engineContext;

public:
    MenuBar(EditorContext& editor, Core::EngineContext& engine)
        : m_editorContext(editor), m_engineContext(engine) {}

    ~MenuBar() = default;

public:
    void Render();
};

}  // namespace PotatoEngine::Editor
