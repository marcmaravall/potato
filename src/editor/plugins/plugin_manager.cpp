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
        if (plugin.Compile(m_luaState)) {
            AddPlugin(std::move(plugin));
        }
    }
}

void PluginManager::OnRender() {
    ImGui::TextUnformatted("TODO: implement");
}

void PluginManager::OnEnd() {
    for (auto& plugin : m_editorPlugins) {
        plugin.Update();
    }
}

}  // namespace PotatoEngine::Editor
