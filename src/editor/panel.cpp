#include "panel.h"

using namespace PotatoEngine::Editor;

void EditorPanel::Render() {
    if (!m_isOpen)
        return;

    OnBegin();
    ImGui::Begin(m_title.c_str(), &m_isOpen, m_flags);

    OnRender();

    ImGui::End();
    OnEnd();
}
