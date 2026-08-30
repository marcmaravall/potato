#include "menu_bar.hpp"

namespace PotatoEngine::Editor {

void MenuBar::Render() {
    if (ImGui::BeginMainMenuBar()) {
        ImGui::Text("Potato Engine");

        ImGui::SameLine();
        ImGui::Separator();

        ImGui::EndMainMenuBar();
    }
}

}  // namespace PotatoEngine::Editor
