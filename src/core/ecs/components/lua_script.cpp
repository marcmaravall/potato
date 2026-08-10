#include "lua_script.h"

#include <ecs/systems/lua_script_system.h>

namespace PotatoEngine::Core::ECS::Components {
bool LuaScript::Compile(sol::state &lua, AssetManager &am) {
    auto *scriptAsset = am.TryGetAsset(m_scriptAssetID);
    if (!scriptAsset) {
        MEB_LOG_ERRORF("Lua script asset with ID %lld not found",
                       m_scriptAssetID);
        return false;
    }

    LuaScriptAsset *luaScriptAsset =
        dynamic_cast<LuaScriptAsset *>(scriptAsset);
    if (!luaScriptAsset) {
        MEB_LOG_ERRORF("Asset with ID %lld is not a Lua script asset",
                       m_scriptAssetID);
        return false;
    }

    if (luaScriptAsset->Compile(lua, m_env)) m_compiled = true;
    return true;
}

bool LuaScript::CallFunction(const char *name) {
    if (!m_compiled) {
        MEB_LOG_WARNINGF("Lua Script with id %lld is not compiled!",
                         m_scriptAssetID);
        return false;
    }

    try {
        sol::protected_function func = m_env[name];
        if (!func.valid()) {
            // MEB_LOG_WARNINGF("Lua function '%s' not found", name);
            return false;
        }

        sol::protected_function_result result = func();
        if (!result.valid()) {
            sol::error err = result;
            MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
            return false;
        }
    } catch (const sol::error &err) {
        MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
        return false;
    }

    return true;
}
}  // namespace PotatoEngine::Core::ECS::Components
