#include "hierarchy.h"

namespace PotatoEngine::Editor {

	void HierarchyPanel::OnBegin() {

	}

    static void RenderEntityNode(Core::ECS::Entity* entity, Core::ECS::Entity*& selectedEntity) {
        ImGuiTreeNodeFlags flags =
            (selectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) |
            ImGuiTreeNodeFlags_OpenOnArrow;

        bool opened = ImGui::TreeNodeEx(
            (void*)entity,
            flags,
            "%s",
            entity->Name.c_str()
        );

        if (ImGui::IsItemClicked()) {
            selectedEntity = entity;
        }

        if (opened) {
            for (auto& child : entity->Children) {
                RenderEntityNode(&child, selectedEntity);
            }

            ImGui::TreePop();
        }
    }

	void HierarchyPanel::OnRender() {

		if (ImGui::BeginPopupContextWindow()) {
			if (ImGui::MenuItem("New Entity")) {
				m_engineContext.Entities.push_back(Core::ECS::Entity("New Entity"));
			}
			ImGui::EndPopup();
		}
		
		for (auto& entity : m_engineContext.Entities) {
			RenderEntityNode(&entity, m_engineContext.SelectedEntity);
		}
	}

	void HierarchyPanel::OnEnd() {

	}
}
