#include "inspector.h"

#include <assets_manager/asset.h>
#include <assets_manager/assets/lua_script_asset.h>
#include <assets_manager/assets/texture_asset.h>
#include <assets_manager/assets_manager.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <ecs/components/isometric_grid.hpp>
#include <glm/glm.hpp>
#include <strstream>

#include "ecs/components/rigidbody2d.hpp"
#include "imgui.h"
#include "rendering/texture2d.h"

namespace PotatoEngine::Editor {

using namespace PotatoEngine::Core::ECS;

void Inspector::RenderFileInput(const char* label, Core::AssetID& asset,
                                Core::AssetType type) {
    auto p_asset = m_engineContext._AssetManager.TryGetAsset(asset);

    if (p_asset) {
        std::filesystem::path scriptPath(p_asset->GetAbsolutePath());
        ImGui::Text("%s", scriptPath.filename().string().c_str());
    } else {
        ImGui::TextDisabled("No file selected");
    }

    if (ImGui::Button("Select Asset")) {
        ImGui::OpenPopup("AssetSelection");
    }

    if (ImGui::BeginPopup("AssetSelection")) {
        const auto& assetsIds = m_engineContext._AssetManager.GetAssets(type);
        for (Core::AssetID id : assetsIds) {
            auto p_currentAsset = m_engineContext._AssetManager.TryGetAsset(id);
            std::filesystem::path path(p_currentAsset->GetAbsolutePath());

            if (ImGui::MenuItem(path.filename().string().c_str())) {
                asset = id;
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::EndPopup();
    }
}

Inspector::Inspector(Core::EngineContext& ctx, EditorContext& ectx)
    : EditorPanel("Inspector", ctx, ectx) {
    // TODO: add undo and redo:

    Registry.Add<Core::ECS::Components::Name>(
        [](Core::ECS::Components::Name& name) {
            if (ImGui::InputText("##Name", &name.Value)) {
            }
        });

    Registry.Add<Core::ECS::Components::LuaScript>(
        [&](Core::ECS::Components::LuaScript& script) {
            ImGui::TextDisabled("Lua Script");
            ImGui::SameLine();
            if (ImGui::Button("Reload")) {
                script.Compile(m_engineContext.GetLuaState(),
                               m_engineContext._AssetManager);
            }

            Core::AssetID s = script.GetScriptAssetID();
            RenderFileInput("Script Asset", s, Core::AssetType::LUA_SCRIPT);
            script.SetScriptAssetID(s);
        });

    Registry.Add<Core::ECS::Components::Transform>(
        [](Core::ECS::Components::Transform& transform) {
            ImGui::InputFloat3("Position", &transform.Position[0]);
            ImGui::InputFloat3("Rotation", &transform.Rotation[0]);
            ImGui::InputFloat3("Scale", &transform.Scale[0]);
        });

    Registry.Add<Core::ECS::Components::IsometricGrid>(
        [](Components::IsometricGrid& grid) {
            ImGui::InputScalar("Width", ImGuiDataType_U64, &grid.Width);
            ImGui::InputScalar("Height", ImGuiDataType_U64, &grid.Height);
            ImGui::InputScalar("Depth", ImGuiDataType_U64, &grid.Depth);
        });

    Registry.Add<Core::ECS::Components::SpriteRenderer>(
        [&](Core::ECS::Components::SpriteRenderer& sr) {
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

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted("Layer");
                ImGui::TableSetColumnIndex(1);
                ImGui::InputInt("##Layer", &sr.Layer);

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);

                Core::AssetID t = sr.GetTextureAssetID();
                RenderFileInput("Texture Asset", t, Core::AssetType::TEXTURE);
                sr.SetTextureAssetID(t);

                ImGui::EndTable();
            }
        });

    Registry.Add<Core::ECS::Components::Parent>(
        [](Core::ECS::Components::Parent& parent) {
            ImGui::TextDisabled("Parent Entity");
            ImGui::SameLine();
            ImGui::Text("%llu", static_cast<long long unsigned>(parent.Value));
        });

    Registry.Add<Core::ECS::Components::Children>(
        [](Core::ECS::Components::Children& children) {
            ImGui::TextDisabled("Children");

            if (children.Value.empty()) {
                ImGui::TextDisabled("None");
                return;
            }

            ImGui::Indent();

            for (auto child : children.Value) {
                ImGui::BulletText("%llu",
                                  static_cast<long long unsigned>(child));
            }

            ImGui::Unindent();
        });

    Registry.Add<Core::ECS::Components::Camera>(
        [](Core::ECS::Components::Camera& camera) {
            ImGui::ColorEdit3("Clear Color", &camera.ClearColor[0]);
            ImGui::InputFloat("Zoom", &camera.Zoom, 0.01f, 100.0f, "%.2f");
        });

    Registry.Add<Core::ECS::Components::BoxCollider2D>(
        [](Core::ECS::Components::BoxCollider2D& collider) {
            ImGui::InputFloat2("Origin", (float*)&collider.Origin);
            ImGui::InputFloat2("Size", (float*)&collider.Size);
        });

    Registry.Add<Core::ECS::Components::Rigidbody2D>(
        [](Core::ECS::Components::Rigidbody2D& rb) {
            ImGui::InputFloat("Mass", &rb.Mass);
            ImGui::InputFloat("GravityForce", &rb.GravityForce);
        });

    // ASSETS ---------------------------------------------------------------
    using namespace PotatoEngine::Core::Rendering;

    // Readonly view of the file
    Registry.Add<Core::LuaScriptAsset>([](Core::LuaScriptAsset& script) {
        std::ifstream file(script.GetAbsolutePath(),
                           std::ios::binary | std::ios::in);
        if (!file.is_open()) {
            return;
        }
        std::string source;
        source = std::string(std::istreambuf_iterator<char>(file),
                             std::istreambuf_iterator<char>());

        ImGui::InputTextMultiline(
            "##FileContent", &source, ImVec2(-FLT_MIN, -FLT_MIN),
            ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_ReadOnly);
    });

    Registry.Add<Core::TextureAsset>([&](Core::TextureAsset& texture) {
        static int filterSelected = static_cast<int>(texture.Settings.Filter);
        static int wrapS = static_cast<int>(texture.Settings.WrapS);
        static int wrapT = static_cast<int>(texture.Settings.WrapT);

        constexpr char* filterOptions[] = {
            (char*)"Point",
            (char*)"Bilinear",
            (char*)"Trilinear",
        };

        constexpr char* wrapOptions[] = {
            (char*)"Repeat", (char*)"Mirrored Repeat", (char*)"Clamp to Edge",
            (char*)"Clamp to Border"};

        if (ImGui::Combo("Filter", &filterSelected, filterOptions, 3)) {
            TextureFilter filter = static_cast<TextureFilter>(filterSelected);
            texture.Settings.Filter = filter;
        }

        if (ImGui::Combo("WrapS", &wrapS, wrapOptions, 4)) {
            TextureWrap wrap = static_cast<TextureWrap>(wrapS);
            texture.Settings.WrapS = wrap;
        }

        if (ImGui::Combo("WrapT", &wrapT, wrapOptions, 4)) {
            TextureWrap wrap = static_cast<TextureWrap>(wrapT);
            texture.Settings.WrapT = wrap;
        }

        ImGui::Separator();
        if (ImGui::Button("Apply")) {
            texture.Load();
            std::string path = texture.GetAbsolutePath();
            path += Core::AssetManager::kMetaExtension;
            m_engineContext._AssetManager.WriteMetaFile(
                path, m_editorContext.SelectedAsset, texture);
        }
    });
}

void Inspector::RenderAsset() {
    using namespace Core;

    AssetID assetID = m_editorContext.SelectedAsset;
    auto* asset = m_engineContext._AssetManager.TryGetAsset(assetID);
    if (!asset) {
        ImGui::TextColored(
            ImVec4(0.8, 0.1, 0.1, 1.0),
            "ERROR: selected asset doesn't exist in the AssetManager Registry");
        return;
    }

    ImGui::TextColored(ImVec4(0.35f, 0.75f, 1.0f, 1.0f), " Asset");
    ImGui::Separator();
    Registry.Render(asset, typeid(*asset));
}

void Inspector::RenderEntity() {
    EntityID entity = m_editorContext.SelectedEntity;
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

    ImGui::TextColored(ImVec4(0.35f, 0.75f, 1.0f, 1.0f), " Entity");
    ImGui::Separator();

    m_engineContext.Registry.ForEachComponent(
        entity, [&](Component* component) {
            ImGui::PushID(component);

            bool visible = true;
            if (ImGui::CollapsingHeader(component->Name.c_str(), &visible,
                                        ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::Indent(8.0f);

                Registry.Render(component);

                ImGui::Unindent(8.0f);
                ImGui::Spacing();
            }

            if (!visible) {
                ImGui::OpenPopup("RemoveComponentPopup");
            }

            if (ImGui::BeginPopupModal("RemoveComponentPopup", nullptr, 0)) {
                ImGui::SeparatorText("Do you want to remove this component?");
                if (ImGui::Button("Yes")) {
                    m_engineContext.Registry.RemoveComponent(entity,
                                                             component->Type());
                }

                ImGui::SameLine();

                if (ImGui::Button("No")) {
                    ImGui::CloseCurrentPopup();
                }
                // TODO: add a "don't show again" checkbox

                ImGui::EndPopup();
            }

            ImGui::PopID();
        });

    ImGui::Spacing();

    if (ImGui::Button("+ Add Component")) {
        ImGui::OpenPopup("AddComponentPopup");
    }

    if (ImGui::BeginPopup("AddComponentPopup")) {
        const auto& components = m_engineContext.Registry.GetComponentNames();

        for (const auto& name : components) {
            if (ImGui::MenuItem(name.c_str())) {
                m_engineContext.Debug.Log(
                    std::format("Added component \"{}\" to entity with ID {}",
                                name, m_editorContext.SelectedEntity));

                m_engineContext.Registry.AddComponentByName(entity, name);

                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::EndPopup();
    }

    ImGui::Spacing();
    ImGui::PopFont();
}

void Inspector::OnBegin() {}

void Inspector::OnRender() {
    if (m_editorContext.IsAssetSelected && m_editorContext.IsEntitySelected) {
        MEB_LOG_ERROR(
            "IsAssetSelected and IsEntitySelected cannot be true at the same "
            "time, setting both to false.");
        m_editorContext.IsAssetSelected = false;
        m_editorContext.IsEntitySelected = false;
        return;
    }

    if (!m_editorContext.IsEntitySelected && !m_editorContext.IsAssetSelected) {
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.0f);
        ImGui::TextDisabled("No asset/entity selected");
        return;
    }

    if (m_editorContext.IsEntitySelected)
        RenderEntity();
    else
        RenderAsset();
}

void Inspector::OnEnd() {}

}  // namespace PotatoEngine::Editor
