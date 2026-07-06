#pragma once

#include <sol/sol.hpp>

#include <string>
#include <ecs/component.h>
#include <meb.h>

namespace PotatoEngine::Core::ECS::Components {
	class LuaScript : public Component {
	private:
		sol::load_result m_chunk;
		sol::environment m_env;
	
	public:
		std::string Source;

	public:
		LuaScript() : Component("Lua Script") {}
		~LuaScript() = default;

		bool Compile(sol::state& lua);
		bool CallFunction(const char* name);

		sol::load_result& GetChunk() { return m_chunk; }
		sol::environment& GetEnvironment() { return m_env; }
		
		void nothing() override {}
	};
}
