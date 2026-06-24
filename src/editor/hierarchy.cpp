#include "hierarchy.h"

namespace PotatoEngine::Editor {
	using namespace Core::ECS;

	void HierarchyPanel::OnBegin() {

	}

    static void RenderEntityNode(Registry& reg, EntityID entity, EntityID& selectedEntity, bool& isEntitySelected) {
        ImGuiTreeNodeFlags flags = (selectedEntity == entity ? 
            ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

        std::string name = "[NULL]";
        auto* nameComponent = reg.TryGetComponent<Components::Name>(entity);
        if (nameComponent)
            name = nameComponent->Value;

        bool opened = ImGui::TreeNodeEx(
            (void*)entity,
            flags,
            "%s",
            name.c_str()
        );

        if (ImGui::IsItemClicked()) {
            selectedEntity = entity;
            isEntitySelected = true;
        }

        float right = ImGui::GetWindowContentRegionMax().x;
        float width = ImGui::CalcTextSize(std::to_string(entity).c_str()).x;

        ImGui::SameLine(right - width - 10);
        ImGui::TextDisabled("%llu", static_cast<uint64_t>(entity));

        auto* children = reg.TryGetComponent<Components::Children>(entity);
        
        if (opened) {
            if (children)
                for (EntityID child : children->Value)
                    RenderEntityNode(reg, child, selectedEntity, isEntitySelected);

            ImGui::TreePop();
        }
    }

	void HierarchyPanel::OnRender() {
		m_engineContext.Registry.Each_Not <Core::ECS::Components::Parent>([&](Core::ECS::EntityID id) {
            RenderEntityNode(m_engineContext.Registry, id, m_engineContext.SelectedEntity, m_engineContext.IsEntitySelected);
		});
	}

	void HierarchyPanel::OnEnd() {

	}
}
