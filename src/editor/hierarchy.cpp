#include "hierarchy.h"

namespace PotatoEngine::Editor {

	void HierarchyPanel::OnBegin() {

	}

	static void RenderEntityNode(Core::ECS::Entity* entity) {
		if (ImGui::TreeNode(entity->Name.c_str())) {
			for (auto& child : entity->Children) {
				RenderEntityNode(&child);
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
			RenderEntityNode(&entity);
		}
	}

	void HierarchyPanel::OnEnd() {

	}
}
