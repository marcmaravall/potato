#pragma once
#include <sol/sol.hpp>

namespace PotatoEngine::Core::Scripting {
	class LuaScript {
	public:
		LuaScript();
		~LuaScript();
		void LoadScript(const std::string& path);
	private:
		sol::state m_luaState;
	};
}
