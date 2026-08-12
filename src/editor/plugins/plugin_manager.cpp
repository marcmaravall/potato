#include "plugin_manager.hpp"

#include "imgui.h"

namespace PotatoEngine::Editor {

PluginManager::PluginManager(Core::EngineContext& ctx, EditorContext& ectx)
    : EditorPanel("Plugin Manager", ctx, ectx) {}

void PluginManager::AddPlugin(const EditorPlugin& plugin) {
    m_editorPlugins.push_back(plugin);
}

void PluginManager::OnBegin() {}

void PluginManager::OnRender() {
    ImGui::TextUnformatted("TODO: implement");
    // TODO: implement

    m_luaState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math,
                              sol::lib::string, sol::lib::table);
    sol_ImGui::Init(m_luaState);
}

void PluginManager::OnEnd() {}

}  // namespace PotatoEngine::Editor
