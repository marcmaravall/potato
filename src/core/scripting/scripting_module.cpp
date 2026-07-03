#include "scripting_module.h"
#include <engine_context.h>

namespace PotatoEngine::Core::Scripting {
	ScriptingModule::ScriptingModule(EngineContext& ctx) : m_ctx(ctx){
		LuaState.open_libraries (
			sol::lib::base, 
			sol::lib::package, 
			sol::lib::math, 
			sol::lib::string, 
			sol::lib::table
		);

		sol::table debug = LuaState.create_named_table("debug");

		debug.set_function("log", [this](const std::string& message) {
			m_ctx.Debug.Log(message);
		});
	}

	ScriptingModule::~ScriptingModule() {
		
	}

	bool ScriptingModule::RunLuaSafe(sol::load_result& chunk, const char* stage) {
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
	
	bool ScriptingModule::CallLuaFunction(sol::function& func, const char* name) {
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
}
