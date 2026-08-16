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
        EditorPlugin plugin =
            EditorPlugin(m_editorContext, m_engineContext, TEST_PLUGIN_ID);
        AddPlugin(std::move(plugin));
    }
}

void PluginManager::OnRender() {
    if (ImGui::Button("Recompile All")) {
        for (auto& plugin : m_editorPlugins) plugin.Compile(m_luaState);
    }

    ImGui::SameLine();
    ImGui::TextDisabled("%zu plugin(s)", m_editorPlugins.size());

    ImGui::Separator();
    ImGui::Spacing();

    int toRemove = -1;
    for (size_t i = 0; i < m_editorPlugins.size(); ++i) {
        auto& plugin = m_editorPlugins[i];

        ImGui::PushID(static_cast<int>(i));

        ImGui::Text("#%zu", i);
        ImGui::SameLine(60.0f);

        if (plugin.IsCompiled()) {
            ImGui::TextColored(ImVec4(0.30f, 0.85f, 0.40f, 1.0f), "Compiled");
        } else {
            ImGui::TextColored(ImVec4(0.95f, 0.65f, 0.25f, 1.0f),
                               "Not compiled");
        }

        const float removeWidth = ImGui::CalcTextSize("Remove").x +
                                  ImGui::GetStyle().FramePadding.x * 2.0f;
        const float compileWidth = ImGui::CalcTextSize("Compile").x +
                                   ImGui::GetStyle().FramePadding.x * 2.0f;

        const float buttonsWidth =
            compileWidth + removeWidth + ImGui::GetStyle().ItemSpacing.x;

        ImGui::SameLine(ImGui::GetWindowWidth() - buttonsWidth - 10.0f);

        if (ImGui::Button("Compile")) {
            plugin.Compile(m_luaState);
        }

        ImGui::SameLine();

        if (ImGui::Button("Remove")) {
            toRemove = static_cast<int>(i);
        }

        ImGui::PopID();

        if (i + 1 < m_editorPlugins.size()) ImGui::Separator();
    }

    if (toRemove >= 0) {
        m_editorPlugins.erase(m_editorPlugins.begin() + toRemove);
    }
}
void PluginManager::OnEnd() {
    for (auto& plugin : m_editorPlugins) {
        if (plugin.IsCompiled()) plugin.Update();
    }
}

}  // namespace PotatoEngine::Editor
