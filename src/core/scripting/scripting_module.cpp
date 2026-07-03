#include "scripting_module.h"

namespace PotatoEngine::Core::Scripting {
	ScriptingModule::ScriptingModule() {
		LuaState.open_libraries (
			sol::lib::base, 
			sol::lib::package, 
			sol::lib::math, 
			sol::lib::string, 
			sol::lib::table
		);
	}

	ScriptingModule::~ScriptingModule() {
		
	}
}
