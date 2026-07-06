#pragma once

#include <ecs/system.h>
#include <meb.h>

#include <sol/sol.hpp>
#include <ecs/components/lua_script.h>

namespace PotatoEngine::Core {
	class EngineContext;
}

namespace PotatoEngine::Core::ECS::Systems {
	constexpr const char* LUA_START_FUNC_NAME = "_start";
	constexpr const char* LUA_UPDATE_FUNC_NAME = "_update";
	constexpr const char* LUA_DESTROY_FUNC_NAME = "_destroy";

	class LuaScriptSystem : public ECS::System {
	private:
		sol::state m_lua;

	public:
		LuaScriptSystem(EngineContext& ctx);

		~LuaScriptSystem() override = default;

	public:
		sol::state& GetLuaState() { return m_lua; }

		bool CallLuaFunction(sol::function& func, const char* name);
		bool RunLuaSafe(sol::load_result& chunk, const char* stage);

		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
}
