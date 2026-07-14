#include "lua_script_asset.h"
#include <assets_manager/assets_manager.h>

namespace PotatoEngine::Core {
	LuaScriptAsset::LuaScriptAsset(const std::string& path) : Asset(path, AssetType::LUA_SCRIPT) {
		
	}

    bool LuaScriptAsset::Compile(sol::state& lua, sol::environment& env) {
        try {
            env = sol::environment(lua, sol::create, lua.globals());
            if (!env.valid()) {
                MEB_LOG_ERROR("Failed to create Lua environment");
                return false;
            }

            sol::load_result loadResult = lua.load_file(m_absPath.string());
            if (!loadResult.valid()) {
                sol::error err = loadResult;
                MEB_LOG_ERRORF("Lua Script Load Error: %s", err.what());
                return false;
            }

            m_chunk = loadResult;
            sol::set_environment(env, m_chunk);

            sol::protected_function_result result = m_chunk();
            if (!result.valid()) {
                sol::error err = result;
                MEB_LOG_ERRORF("Lua Script Runtime Error: %s", err.what());
                return false;
            }
        }
        catch (const sol::error& err) {
            MEB_LOG_ERRORF("Lua Script Error: %s", err.what());
            return false;
        }

        MEB_LOG_INFOF("Lua script '%s' compiled successfully", m_absPath.string().c_str());
        return true;
    }
};
