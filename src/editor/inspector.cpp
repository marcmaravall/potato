#include "inspector.h"

using namespace PotatoEngine::Editor;

void Inspector::OnBegin() {

}

void Inspector::OnRender() {
    ImGui::SeparatorText("Inspector");
    
    if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::MenuItem("New")) {

        }

        // if (ImGui::MenuItem(""))

        ImGui::EndPopup();
    }
} 

void Inspector::OnEnd() {

}
