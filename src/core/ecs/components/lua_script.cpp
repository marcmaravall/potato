#include "lua_script.h"
#include <ecs/systems/lua_script_system.h>

namespace PotatoEngine::Core::ECS::Components {
	bool LuaScript::Compile(sol::state& lua) {
		try {
			m_env = sol::environment(lua, sol::create, lua.globals());
			if (m_env == sol::nil) {
				MEB_LOG_ERROR("Failed to create Lua environment");
				return false;
			}

			m_chunk = lua.load(Source);

			sol::protected_function_result result = m_chunk(m_env);

			if (!result.valid()) {
				sol::error err = result;
				MEB_LOG_ERRORF("Lua Script Error: %s", err.what());
				return false;
			}

		} catch (const sol::error& err) {
			MEB_LOG_ERRORF("Lua Script Error: %s", err.what());
			return false;
		}

		MEB_LOG_INFO("Lua script compiled successfully");

		return true;
	}

	bool LuaScript::CallFunction(const char* name) {
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
		}
		catch (const sol::error& err) {
			MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
			return false;
		}

		return true;
	}
}
