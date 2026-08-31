#include "menu_bar.hpp"

#include <cstdlib>

namespace PotatoEngine::Editor {

void MenuBar::File() {
    // FIXME: applications freezes when opening or saving a project
    // SOLUTION: add a queue of instructions (save/open) at the end of the frame

    if (ImGui::Button("Open")) {
        m_editorContext.UserOpenProject(m_engineContext);
    }
    if (ImGui::Button("Save")) {
        m_editorContext.UserSaveProject(m_engineContext);
    }
    ImGui::Separator();
    if (ImGui::Button("Exit")) {
        exit(EXIT_SUCCESS);
    }

    ImGui::EndMenu();
}

void MenuBar::Edit() { ImGui::EndMenu(); }

void MenuBar::View() { ImGui::EndMenu(); }

void MenuBar::Help() {
    if (ImGui::Button("Welcome")) {
    }
    if (ImGui::Button("Documentation")) {
    }

    ImGui::EndMenu();
}

void MenuBar::Render() {
    if (ImGui::BeginMainMenuBar()) {
        ImGui::Text("Potato Engine");

        ImGui::Separator();
        if (ImGui::BeginMenu("File")) File();
        ImGui::Separator();
        if (ImGui::BeginMenu("Edit")) Edit();
        ImGui::Separator();
        if (ImGui::BeginMenu("View")) View();
        ImGui::Separator();
        if (ImGui::BeginMenu("Help")) Help();

        ImGui::EndMainMenuBar();
    }
}

}  // namespace PotatoEngine::Editor
