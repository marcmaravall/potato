#include "lua_script_system.h"

namespace PotatoEngine::Core::ECS::Systems {
    void LuaScriptSystem::OnStart() {
        m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			sol::load_result chunk = m_context.Scripting.LuaState.load(script.Source);

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
			sol::function startFunc = result[Scripting::LUA_START_FUNC_NAME];
			m_context.Scripting.CallLuaFunction(startFunc, Scripting::LUA_START_FUNC_NAME);
        });
    }

	// TODO: implement update and destroy functions for Lua scripts
	void LuaScriptSystem::OnUpdate() {
		m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			sol::function updateFunc = m_context.Scripting.LuaState["_update"];
			if (updateFunc.valid())
				updateFunc();
		});
	}

	void LuaScriptSystem::OnDestroy() {
		m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			sol::function destroyFunc = m_context.Scripting.LuaState["_destroy"];
			if (destroyFunc.valid())
				destroyFunc();
		});
	}
}
