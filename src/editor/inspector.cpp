#include "inspector.h"
#include <misc/cpp/imgui_stdlib.h>

using namespace PotatoEngine::Editor;

void Inspector::OnBegin() {

}

void Inspector::OnRender() {
    auto* entity = m_engineContext.SelectedEntity;

    if (!entity) {
        ImGui::TextDisabled("No entity selected");
        return;
    }

    ImGui::Text("Entity");
    ImGui::Separator();

    ImGui::PushItemWidth(-1);
    ImGui::InputText("##EntityName", &entity->Name);
    ImGui::PopItemWidth();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    for (auto component : entity->Components) {
        if (ImGui::CollapsingHeader(component->Name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::PushID(component);
			Registry.Render(component);
			ImGui::Spacing();
            ImGui::PopID();
        }
    }

    ImGui::Spacing();

    if (ImGui::Button("Add Component", ImVec2(-1, 0))) {

    }
}

void Inspector::OnEnd() {

}
