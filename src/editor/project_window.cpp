#include "project_window.h"

#include "imgui.h"

namespace PotatoEngine::Editor {

void ProjectWindow::OnBegin() {}

void ProjectWindow::OnRender() {
    std::string path = m_engineContext._AssetManager.Path(
        m_engineContext._AssetManager.GetRoot() +
        "/assets/tests/project_test.json");

    if (ImGui::Button("Save test")) {
        m_editorContext.CurrentProject->SaveToFile(path);
    }
    ImGui::SameLine();
    if (ImGui::Button("Load From File")) {
        m_editorContext.CurrentProject->LoadFromFile(path);
    }
}

void ProjectWindow::OnEnd() {}
}  // namespace PotatoEngine::Editor
