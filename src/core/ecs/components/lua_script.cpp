#include "lua_script.h"

#include <ecs/systems/lua_script_system.h>

#include <scripting/scripting_utils.hpp>

namespace PotatoEngine::Core::ECS::Components {

using namespace Scripting;

bool LuaScript::Compile(sol::state &lua, AssetManager &am) {
    return Scripting::ScriptingUtils::CompileScript(lua, m_env, am, m_compiled,
                                                    m_scriptAssetID);
}

bool LuaScript::CallFunction(const char *name) {
    return ScriptingUtils::CallLuaFunction(m_env, name, m_compiled,
                                           m_scriptAssetID);
}
}  // namespace PotatoEngine::Core::ECS::Components
