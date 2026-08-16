#include "plugin.hpp"

#include "scripting/scripting_utils.hpp"

namespace PotatoEngine::Editor {

using namespace PotatoEngine::Core;
using namespace PotatoEngine::Core::Scripting;

// TODO: save script for not dynamic_casting every time
bool EditorPlugin::Compile(sol::state& lua) {
    return ScriptingUtils::CompileScript(lua, m_env,
                                         m_engineContext->_AssetManager,
                                         m_compiled, m_pluginAssetID);
}

void EditorPlugin::Update() {
    Core::LuaScriptAsset* script = dynamic_cast<Core::LuaScriptAsset*>(
        m_engineContext->_AssetManager.TryGetAsset(m_pluginAssetID));
    if (!script) {
        MEB_LOG_ERROR("script is null");
        return;
    }

    ScriptingUtils::CallLuaFunction(m_env, "_update", m_compiled,
                                    m_pluginAssetID);
}

}  // namespace PotatoEngine::Editor
