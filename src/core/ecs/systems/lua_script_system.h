#pragma once

#include <ecs/system.h>
#include <engine_context.h>
#include <meb.h>

#include <sol/sol.hpp>
#include <ecs/components/lua_script.h>

namespace PotatoEngine::Core::ECS::Systems {
	constexpr const char* LUA_START_FUNC_NAME = "_start";
	constexpr const char* LUA_UPDATE_FUNC_NAME = "_update";
	constexpr const char* LUA_DESTROY_FUNC_NAME = "_destroy";

	class LuaScriptSystem : public ECS::System {
	private:
		sol::state m_lua;

	public:
		LuaScriptSystem(EngineContext& ctx);

		~LuaScriptSystem() = default;

	public:
		bool CallLuaFunction(sol::function& func, const char* name);
		bool RunLuaSafe(sol::load_result& chunk, const char* stage);

		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
}
