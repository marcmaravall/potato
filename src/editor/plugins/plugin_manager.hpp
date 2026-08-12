#pragma once

#include <core/engine_context.h>
#include <imgui.h>
#include <editor/panel.h>
#include <platform/api.h>
#include <sol2_ImGui_Bindings/sol_ImGui.h>

#include <sol/sol.hpp>

#include "editor/panel.h"
#include "plugin.hpp"

namespace PotatoEngine::Editor {

class PluginManager : public EditorPanel {
private:
    sol::state m_luaState;
    std::vector<EditorPlugin> m_editorPlugins;

public:
    sol::state_view GetLuaState() { return m_luaState; }

    void AddPlugin(const EditorPlugin&);

public:
    PluginManager(Core::EngineContext& ctx, EditorContext& ectx);

protected:
    void OnBegin() override;
    void OnRender() override;
    void OnEnd() override;
};

}  // namespace PotatoEngine::Editor
