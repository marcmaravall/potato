#pragma once

#include <sol/sol.hpp>

namespace PotatoEngine::Core::Scripting {
	class ScriptingModule {
	private:
		sol::state LuaState;

	public:
		ScriptingModule();
		~ScriptingModule();
	};
}
