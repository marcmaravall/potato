#include "lua_script_system.h"
#include <engine_context.h>

namespace PotatoEngine::Core::ECS::Systems {
	using namespace ECS::Components;

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

		sol::table reg = m_lua.create_named_table("registry");
		reg.set_function("create", [&ctx](const std::string& name) -> EntityID {
			return ctx.Registry.CreateEntity(name);
		});

		reg.set_function("get_component", [&ctx](sol::this_state ts, EntityID e, const std::string& name) -> sol::object {
			sol::state_view lua(ts);

			for (const auto& comp : ctx.Registry.GetComponentNames()) {
				if (name == comp) {
					Component* c = ctx.Registry.GetComponentByName(e, name);
					MEB_ASSERT(c);

					return ctx.Registry.BindComponentToLua(lua, c, name);
				}
			}

			return sol::nil;
		});

		// usertypes:

		// example
		m_lua.new_usertype<Component>("Component");

		m_lua.new_usertype<Name>("Name",
			sol::constructors<Name(const std::string& name)>(),
			"value", &Name::Value,
			sol::base_classes, sol::bases<Component>()
		);
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

		try {
			sol::protected_function_result r = func();
			if (!r.valid()) {
				sol::error err = r;
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

    void LuaScriptSystem::OnStart() {
        m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			script.CallFunction(LUA_START_FUNC_NAME);
        });
    }

	void LuaScriptSystem::OnUpdate() {
		m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			script.CallFunction(LUA_UPDATE_FUNC_NAME);
		});
	}

	void LuaScriptSystem::OnDestroy() {
		m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
			script.CallFunction(LUA_DESTROY_FUNC_NAME);
		});
	}
}
