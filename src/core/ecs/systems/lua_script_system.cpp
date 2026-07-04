#include "lua_script_system.h"

namespace PotatoEngine::Core::ECS::Systems {
	LuaScriptSystem::LuaScriptSystem(EngineContext& ctx) : ECS::System(ctx) {
		m_lua.open_libraries(
			sol::lib::base,
			sol::lib::package,
			sol::lib::math,
			sol::lib::string,
			sol::lib::table
		);

		sol::table debug = m_lua.create_named_table("debug");

		debug.set_function("log", [&ctx](const std::string& message) {
			ctx.Debug.Log(message);
		});
	}

	bool LuaScriptSystem::RunLuaSafe(sol::load_result& chunk, const char* stage) {
		if (!chunk.valid()) {
			sol::error err = chunk;
			MEB_LOG_ERRORF("Lua compile error (%s): %s", stage, err.what());
			return false;
		}

		sol::protected_function_result result = chunk();

		if (!result.valid()) {
			sol::error err = result;
			MEB_LOG_ERRORF("Lua runtime error (%s): %s", stage, err.what());
			return false;
		}

		return true;
	}

	bool LuaScriptSystem::CallLuaFunction(sol::function& func, const char* name) {
		if (!func.valid()) {
			MEB_LOG_WARNINGF("Lua function '%s' not found", name);
			return false;
		}

		sol::protected_function_result r = func();

		if (!r.valid()) {
			sol::error err = r;
			MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
			return false;
		}

		return true;
	}

    void LuaScriptSystem::OnStart() {
        m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			sol::load_result chunk = m_lua.load(script.Source);

			if (!chunk.valid()) {
				sol::error err = chunk;
				MEB_LOG_ERROR(err.what());
				return;
			}

			sol::protected_function_result exec = chunk();

			if (!exec.valid()) {
				sol::error err = exec;
				MEB_LOG_ERROR(err.what());
				return;
			}

			if (exec.get_type() != sol::type::table) {
				MEB_LOG_WARNING("Lua script must return a table.");
				return;
			}

			sol::table result = exec;
			sol::function startFunc = result[LUA_START_FUNC_NAME];
			CallLuaFunction(startFunc, LUA_START_FUNC_NAME);
        });
    }

	// TODO: implement update and destroy functions for Lua scripts
	void LuaScriptSystem::OnUpdate() {
		m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			sol::function updateFunc = m_lua[LUA_UPDATE_FUNC_NAME];
			if (updateFunc.valid())
				updateFunc();
		});
	}

	void LuaScriptSystem::OnDestroy() {
		m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			sol::function destroyFunc = m_lua["_destroy"];
			if (destroyFunc.valid())
				destroyFunc();
		});
	}
}
