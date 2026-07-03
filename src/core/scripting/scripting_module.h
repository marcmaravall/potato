// TODO: remove this module so lua_script_system only exists and handles lua scripts directly

#pragma once

#include <sol/sol.hpp>
#include <core/logging/debug.h>

namespace PotatoEngine::Core {
	class EngineContext;
}

namespace PotatoEngine::Core::Scripting {
	constexpr const char* LUA_START_FUNC_NAME = "_start";
	constexpr const char* LUA_UPDATE_FUNC_NAME = "_update";
	constexpr const char* LUA_DESTROY_FUNC_NAME = "_destroy";

	class ScriptingModule {
	private:
		EngineContext& m_ctx;

	public:
		sol::state LuaState;

	public:
		ScriptingModule(EngineContext& ctx);
		~ScriptingModule();
	
	public:
		bool RunLuaSafe(sol::load_result& chunk, const char* stage);
		bool CallLuaFunction(sol::function& func, const char* name);
	};
}
