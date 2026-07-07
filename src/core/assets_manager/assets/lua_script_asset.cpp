#include "lua_script_asset.h"
#include <assets_manager/assets_manager.h>

namespace PotatoEngine::Core {
	LuaScriptAsset::LuaScriptAsset(const std::string& path, sol::state& lua) : Asset(path, AssetType::LUA_SCRIPT) {
		
	}

	bool LuaScriptAsset::Compile(sol::state& lua, sol::environment& env) {
		try {
			env = sol::environment(lua, sol::create, lua.globals());
			if (env == sol::nil) {
				MEB_LOG_ERROR("Failed to create Lua environment");
				return false;
			}

			m_chunk = lua.load_file(m_absPath.string());

			sol::protected_function_result result = m_chunk(env);

			if (!result.valid()) {
				sol::error err = result;
				MEB_LOG_ERRORF("Lua Script Error: %s", err.what());
				return false;
			}

		}
		catch (const sol::error& err) {
			MEB_LOG_ERRORF("Lua Script Error: %s", err.what());
			return false;
		}

		MEB_LOG_INFO("Lua script compiled successfully");

		return true;
	}
};
