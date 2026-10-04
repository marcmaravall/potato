#include "plugin_manager.hpp"

#include <editor/scripting/editor_api.hpp>
#include <scripting/scripting_api.hpp>
#include <scripting/scripting_utils.hpp>

#include "assets_manager/asset.h"
#include "editor/utils/imgui_utils.hpp"
#include "imgui.h"

namespace PotatoEngine::Editor {

using namespace Core;
using namespace Core::Scripting;

PluginManager::PluginManager(Core::EngineContext& ctx, EditorContext& ectx)
    : EditorPanel("Plugin Manager", ctx, ectx) {
    ScriptingUtils::OpenLuaLibs(m_luaState);
    sol_ImGui::Init(m_luaState);
    ScriptingAPI::InitCore(m_luaState, ctx);
    Scripting::InitEditor(m_luaState);
}

void PluginManager::AddPlugin(EditorPlugin plugin) {
    m_editorPlugins.push_back(std::move(plugin));
}

void PluginManager::OnBegin() {}

void PluginManager::OnRender() {
    if (ImGui::Button("Recompile All")) {
        for (auto& plugin : m_editorPlugins) plugin.Compile(m_luaState);
    }

    ImGui::SameLine();
    ImGui::TextDisabled("%zu plugin(s)", m_editorPlugins.size());

    if (ImGui::Button("Add plugin")) {
        if (m_selectedAsset) {
            auto plugin =
                EditorPlugin(m_editorContext, m_engineContext, m_selectedAsset);
            AddPlugin(plugin);
        }
    }
    ImGui::SameLine();
    Utils::ImGuiUtils::RenderFileInput("Select asset", m_selectedAsset,
                                       Core::AssetType::LUA_SCRIPT,
                                       m_engineContext);

    ImGui::Separator();
    ImGui::Spacing();

    int toRemove = -1;
    for (size_t i = 0; i < m_editorPlugins.size(); ++i) {
        auto& plugin = m_editorPlugins[i];
        const bool compiled = plugin.IsCompiled();

        ImGui::PushID(static_cast<int>(i));

        ImGui::TextDisabled("%zu", i);
        ImGui::SameLine(40.0f);

        ImGui::BeginGroup();
        if (compiled) {
            const PluginMeta& meta = plugin.GetMeta();
            ImGui::Text("%s", meta.Name.c_str());
            ImGui::SameLine();
            ImGui::TextDisabled("v%s", meta.Version.c_str());
            ImGui::TextColored(ImVec4(0.30f, 0.85f, 0.40f, 1.0f), "Compiled");
            if (!meta.Description.empty()) {
                ImGui::SameLine();
                ImGui::TextDisabled("- %s", meta.Description.c_str());
            }
        } else {
            ImGui::TextDisabled("Unnamed plugin");
            ImGui::TextColored(ImVec4(0.95f, 0.65f, 0.25f, 1.0f),
                               "Not compiled");
        }
        ImGui::EndGroup();

        const float removeWidth = ImGui::CalcTextSize("Remove").x +
                                  ImGui::GetStyle().FramePadding.x * 2.0f;

        const char* compileLabel = compiled ? "Remcompile" : "Compile";
        const float compileWidth = ImGui::CalcTextSize(compileLabel).x +
                                   ImGui::GetStyle().FramePadding.x * 2.0f;
        const float buttonsWidth =
            compileWidth + removeWidth + ImGui::GetStyle().ItemSpacing.x;

        ImGui::SameLine(ImGui::GetContentRegionMax().x - buttonsWidth);

        if (ImGui::Button(compileLabel)) {
            plugin.Compile(m_luaState);
            plugin.OnLoad();
        }

        ImGui::SameLine();

        if (ImGui::Button("Remove")) {
            toRemove = static_cast<int>(i);
        }

        ImGui::PopID();
        ImGui::Separator();
    }

    if (toRemove >= 0) {
        m_editorPlugins[toRemove].Exit();
        m_editorPlugins.erase(m_editorPlugins.begin() + toRemove);
    }
}

void PluginManager::OnEnd() {
    for (auto& plugin : m_editorPlugins) {
        if (plugin.IsCompiled()) plugin.Update();
    }
}

void PluginManager::OnExitEditor() {
    for (auto& plugin : m_editorPlugins) {
        plugin.Exit();
    }
}

}  // namespace PotatoEngine::Editor
