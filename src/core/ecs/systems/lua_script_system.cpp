#include "lua_script_system.h"

#include <engine_context.h>

#include "scripting/scripting_api.hpp"

namespace PotatoEngine::Core::ECS::Systems {
using namespace ECS::Components;

LuaScriptSystem::LuaScriptSystem(EngineContext& ctx) : ECS::System(ctx) {
    m_lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math,
                         sol::lib::string, sol::lib::table);

    Scripting::ScriptingAPI::InitCore(m_lua, ctx);

    // misc:
    // TODO: move to scripting_api.hpp
    sol::table debug = m_lua.create_named_table("Debug");

    debug.set_function(
        "log", [&ctx](const std::string& message) { ctx.Debug.Log(message); });

    sol::table reg = m_lua.create_named_table("Registry");
    reg.set_function("create", [&ctx](const std::string& name) -> EntityID {
        return ctx.Registry.CreateEntity(name);
    });

    reg.set_function(
        "getComponent",
        [&ctx](sol::this_state ts, EntityID e,
               const std::string& name) -> sol::object {
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
    // ------
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
    } catch (const sol::error& err) {
        MEB_LOG_ERRORF("Lua runtime error (%s): %s", name, err.what());
        return false;
    }

    return true;
}

void LuaScriptSystem::OnStart() {
    try {
        m_context.Registry.Each<Components::LuaScript>([&](auto& script) {
            MEB_LOG_INFOF("Calling lua start to script with assetid: %lld",
                          script.GetScriptAssetID());
            script.CallFunction(LUA_START_FUNC_NAME);
        });

    } catch (std::exception& ex) {
        MEB_LOG_ERRORF("Exception: %s", ex.what());
    }
}

void LuaScriptSystem::OnUpdate() {
    try {
        m_context.Registry.Each<Components::LuaScript>(
            [&](auto& script) { script.CallFunction(LUA_UPDATE_FUNC_NAME); });
    } catch (std::exception& ex) {
        MEB_LOG_ERRORF("Exception: %s", ex.what());
    }
}

void LuaScriptSystem::OnDestroy() {
    try {
        m_context.Registry.Each<Components::LuaScript>(
            [&](auto& script) { script.CallFunction(LUA_DESTROY_FUNC_NAME); });

    } catch (std::exception& ex) {
        MEB_LOG_ERRORF("Exception: %s", ex.what());
    }
}
}  // namespace PotatoEngine::Core::ECS::Systems
