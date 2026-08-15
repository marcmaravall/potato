#include "plugin_manager.hpp"

#include "imgui.h"

namespace PotatoEngine::Editor {

PluginManager::PluginManager(Core::EngineContext& ctx, EditorContext& ectx)
    : EditorPanel("Plugin Manager", ctx, ectx) {
    
    m_luaState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math,
                              sol::lib::string, sol::lib::table);
    sol_ImGui::Init(m_luaState);
}

void PluginManager::AddPlugin(const EditorPlugin& plugin) {
    m_editorPlugins.push_back(plugin);
}

void PluginManager::OnBegin() {
    static bool init = false;
    if (!init) {
        init = true;

        // TEST:
#define TEST_PLUGIN_ID 5409846884224673654
        EditorPlugin plugin = EditorPlugin(m_editorContext, m_engineContext, TEST_PLUGIN_ID);
        AddPlugin(std::move(plugin));
    }
}

void PluginManager::OnRender() {
    ImGui::SetNextItemWidth(120);
    if (ImGui::Button("Recompile all Plugins")) {
        for (auto& plugin : m_editorPlugins) plugin.Compile(m_luaState);
    }
    ImGui::Separator();

    int toRemove = -1;
    const auto size = m_editorPlugins.size();
    for (size_t i = 0; i < size; i++) {
        auto& plugin = m_editorPlugins[i];

        ImGui::Text("%lld --- ", i);
        ImGui::SameLine();
        ImGui::Text("Compiled: %s",
                    (int)plugin.IsCompiled() ? "Yes" : "No");
        ImGui::SameLine();
        if (ImGui::Button("Compile")) {
            plugin.Compile(m_luaState);
        }
        ImGui::SameLine();
        if (ImGui::Button("Remove")) {
            toRemove = i;
        }
        ImGui::Separator();
    }

    // TODO: remove at index i
}

void PluginManager::OnEnd() {
    for (auto& plugin : m_editorPlugins) {
        if (plugin.IsCompiled())
            plugin.Update();
    }
}

}  // namespace PotatoEngine::Editor
