#include "scripting_utils.hpp"

#include "assets_manager/asset.h"
#include "assets_manager/assets/lua_script_asset.h"

namespace PotatoEngine::Core::Scripting {

bool ScriptingUtils::CompileScript(sol::state& lua, sol::environment& env,
                                   AssetManager& am, bool& compiled,
                                   AssetID assetID) {
    auto* scriptAsset = am.TryGetAsset(assetID);
    if (!scriptAsset) {
        MEB_LOG_ERRORF("Lua script asset with ID %lld not found", assetID);
        return false;
    }

    LuaScriptAsset* luaScriptAsset = dynamic_cast<LuaScriptAsset*>(scriptAsset);
    if (!luaScriptAsset) {
        MEB_LOG_ERRORF("Asset with ID %lld is not a Lua script asset", assetID);
        return false;
    }

    if (luaScriptAsset->Compile(lua, env)) compiled = true;
    return compiled;
}

bool ScriptingUtils::CallLuaFunction(sol::environment& env, const char* name,
                                     bool& compiled, AssetID asset) {
    if (!compiled) {
        MEB_LOG_WARNINGF("Lua Script with id %lld is not compiled!", asset);
        return false;
    }

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

}  // namespace PotatoEngine::Core::Scripting
