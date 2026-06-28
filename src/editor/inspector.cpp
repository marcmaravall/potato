#include "inspector.h"
#include <misc/cpp/imgui_stdlib.h>

namespace PotatoEngine::Editor {
    
    using namespace PotatoEngine::Core::ECS;
    
    Inspector::Inspector(Core::EngineContext& ctx, EditorContext& ectx) : EditorPanel("Inspector", ctx, ectx) {
        Registry.Add<Core::ECS::Components::Name>([](Core::ECS::Components::Name& name) {
            char buffer[256]{};
            strcpy(buffer, name.Value.c_str());

            if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
                name.Value = buffer;
        });

        Registry.Add<Core::ECS::Components::Transform>([](Core::ECS::Components::Transform& transform) {
            ImGui::InputFloat3("Position", &transform.Position[0]);
            ImGui::InputFloat3("Rotation", &transform.Rotation[0]);
            ImGui::InputFloat3("Scale", &transform.Scale[0]);
        });

        Registry.Add<Core::ECS::Components::SpriteRenderer>([](Core::ECS::Components::SpriteRenderer& sr) {
            if (ImGui::BeginTable("SpriteRenderer", 2)) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted("Color");
                ImGui::TableSetColumnIndex(1);
                ImGui::ColorEdit4("##Color", &sr.Color[0]);

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted("Pivot");
                ImGui::TableSetColumnIndex(1);
                ImGui::InputFloat2("##Pivot", &sr.Pivot[0]);

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted("Flip X");
                ImGui::TableSetColumnIndex(1);
                ImGui::Checkbox("##FlipX", &sr.FlipX);

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted("Flip Y");
                ImGui::TableSetColumnIndex(1);
                ImGui::Checkbox("##FlipY", &sr.FlipY);

                ImGui::EndTable();
            }
        });

        Registry.Add<Core::ECS::Components::Parent>([](Core::ECS::Components::Parent& parent) {
            ImGui::TextDisabled("Parent Entity");
            ImGui::SameLine();
            ImGui::Text("%llu", static_cast<long long unsigned>(parent.Value));
        });

        Registry.Add<Core::ECS::Components::Children>([](Core::ECS::Components::Children& children) {
            ImGui::TextDisabled("Children");

            if (children.Value.empty()) {
                ImGui::TextDisabled("None");
                return;
            }

            ImGui::Indent();

            for (auto child : children.Value) {
                ImGui::BulletText(
                    "%llu",
                    static_cast<long long unsigned>(child));
            }

            ImGui::Unindent();
        });

        Registry.Add<Core::ECS::Components::Camera>([](Core::ECS::Components::Camera& camera) {
            ImGui::ColorEdit3("Clear Color", &camera.ClearColor[0]);
        });
    }

    void Inspector::OnBegin() {
    
    }
    
    void Inspector::OnRender() {
        if (!m_editorContext.IsEntitySelected) {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.0f);
            ImGui::TextDisabled("No entity selected");
            return;
        }
    
        EntityID entity = m_editorContext.SelectedEntity;
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    
        ImGui::TextColored(
            ImVec4(0.35f, 0.75f, 1.0f, 1.0f),
            " Entity"
        );
    
        m_engineContext.Registry.ForEachComponent(entity, [&](Component* component) {
            ImGui::PushID(component);
            
            if (ImGui::CollapsingHeader(component->Name.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::Indent(8.0f);

                Registry.Render(component);

                ImGui::Unindent(8.0f);
                ImGui::Spacing();
            }
    
            ImGui::PopID();
        });
    
        ImGui::Spacing();
    
        if (ImGui::Button("+ Add Component")) {
            ImGui::OpenPopup("AddComponentPopup");
        }

        if (ImGui::BeginPopup("AddComponentPopup")) {
            const auto& components = Registry.GetComponentNames();
        
            for (const auto& name : components) {
                if (ImGui::MenuItem(name.c_str())) {
                    m_engineContext.Debug.Log(std::format("Added component \"{}\" to entity with ID {}", name, m_editorContext.SelectedEntity));
                    ImGui::CloseCurrentPopup();
                }
            }
        
            ImGui::EndPopup();
        }
    
        ImGui::Spacing();
        ImGui::PopFont();
    }
    
    void Inspector::OnEnd() {
    
    }
    
}