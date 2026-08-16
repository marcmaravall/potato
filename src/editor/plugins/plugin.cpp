#include "plugin.hpp"

namespace PotatoEngine::Editor {

using namespace PotatoEngine::Core;

// TODO: don't copy the code from LuaScript, add a generic sol2 module
bool CallFunction(const char* name, sol::environment& env) {
    try {
        sol::protected_function func = env[name];
        if (!func.valid()) {
            return false;
        }

        sol::protected_function_result result = func();
        if (!result.valid()) {
            sol::error err = result;
            MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
            return false;
        }
    } catch (const sol::error& err) {
        MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
        return false;
    }

    return true;
}

// TODO: save script for not dynamic_casting every time
bool EditorPlugin::Compile(sol::state& lua) {
    auto* scriptAsset =
        m_engineContext->_AssetManager.TryGetAsset(m_pluginAssetID);
    if (!scriptAsset) {
        MEB_LOG_ERRORF("Lua script asset with ID %lld not found",
                       m_pluginAssetID);
        return false;
    }

    LuaScriptAsset* luaScriptAsset = dynamic_cast<LuaScriptAsset*>(scriptAsset);
    if (!luaScriptAsset) {
        MEB_LOG_ERRORF("Asset with ID %lld is not a Lua script asset",
                       m_pluginAssetID);
        return false;
    }

    if (luaScriptAsset->Compile(lua, m_env)) m_compiled = true;
    return true;
}

void EditorPlugin::Update() {
    Core::LuaScriptAsset* script = dynamic_cast<Core::LuaScriptAsset*>(
        m_engineContext->_AssetManager.TryGetAsset(m_pluginAssetID));
    if (!script) {
        MEB_LOG_ERROR("script is null");
        return;
    }

    CallFunction("_update", m_env);
}

}  // namespace PotatoEngine::Editor
