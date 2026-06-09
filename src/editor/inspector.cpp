#include "inspector.h"
#include <misc/cpp/imgui_stdlib.h>

using namespace PotatoEngine::Editor;

void Inspector::OnBegin() {

}

void Inspector::OnRender() {
    auto* entity = m_engineContext.SelectedEntity;

    if (!entity) {
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.0f);
        ImGui::TextDisabled("No entity selected");
        return;
    }

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

    ImGui::TextColored(
        ImVec4(0.35f, 0.75f, 1.0f, 1.0f),
        " Entity"
    );

    ImGui::Separator();

    ImGui::PushItemWidth(-1);
    ImGui::InputTextWithHint("##EntityName", "Entity Name", &entity->Name);
    ImGui::PopItemWidth();

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(0.9f, 0.9f, 0.9f, 1.0f), "Components");

    ImGui::Separator();

    for (auto* component : entity->Components) {
        ImGui::PushID(component);

        if (ImGui::CollapsingHeader(component->Name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Indent(8.0f);

            Registry.Render(component);

            ImGui::Unindent(8.0f);
            ImGui::Spacing();
        }

        ImGui::PopID();
    }

    ImGui::Spacing();

    if (ImGui::Button("+ Add Component", ImVec2(-1, 32))) {

    }

    ImGui::Spacing();

    if (!entity->Systems.empty()) {
        ImGui::TextColored(
            ImVec4(0.9f, 0.9f, 0.9f, 1.0f),
            "Systems"
        );

        ImGui::Separator();

        for (auto* system : entity->Systems) {
            ImGui::PushID(system);

            if (ImGui::CollapsingHeader(
                system->Name.c_str(),
                ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Indent(8.0f);

                ImGui::TextDisabled("%s", system->Name.c_str());

                ImGui::Unindent(8.0f);
                ImGui::Spacing();
            }

            ImGui::PopID();
        }
    }

    ImGui::PopFont();
}

void Inspector::OnEnd() {

}
