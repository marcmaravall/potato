#include "hierarchy.h"

namespace PotatoEngine::Editor {
	using namespace Core::ECS;

	void HierarchyPanel::OnBegin() {

	}

    void HierarchyPanel::RenderEntityNode(EntityID entity, EntityID& toDelete) {
        auto& selectedEntity = m_editorContext.SelectedEntity;
        auto& isEntitySelected = m_editorContext.IsEntitySelected;
        auto& reg = m_engineContext.Registry;
        auto& ctx = m_engineContext;

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

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("New")) {
                EntityID child = ctx.Registry.CreateEntity("New entity");
                ctx.Registry.AddComponent<Components::Parent>(child, selectedEntity);

                auto* children = ctx.Registry.TryGetComponent<Components::Children>(selectedEntity);
                if (!children)
                    children = &ctx.Registry.AddComponent<Components::Children>(selectedEntity);
                children->Value.push_back(child);
            }
            
            if (ImGui::MenuItem("Delete")) {
                toDelete = entity;
            }
        
            ImGui::EndPopup();
        }

        float right = ImGui::GetWindowContentRegionMax().x;
        float width = ImGui::CalcTextSize(std::to_string(entity).c_str()).x;

        ImGui::SameLine(right - width - 10);
        ImGui::TextDisabled("%llu", static_cast<long long unsigned>(entity));

        auto* children = reg.TryGetComponent<Components::Children>(entity);
        
        if (opened) {
            if (children)
                for (EntityID child : children->Value)
                    RenderEntityNode(child, toDelete);

            ImGui::TreePop();
        }
    }

	void HierarchyPanel::OnRender() {
        EntityID toDelete = NULL_ENTITY;
		m_engineContext.Registry.Each_Not <Core::ECS::Components::Parent>([&](Core::ECS::EntityID id) {
            RenderEntityNode(id, toDelete);
		});

        if (toDelete != NULL_ENTITY) {
            m_editorContext.IsEntitySelected = false;
            m_engineContext.Registry.RemoveEntity(toDelete);
        }        
    }

	void HierarchyPanel::OnEnd() {

	}
}
