#pragma once

#include <ecs/system.h>
#include <engine_context.h>
#include <meb.h>

#include <ecs/components/lua_script.h>

namespace PotatoEngine::Core::ECS::Systems {
	class LuaScriptSystem : public ECS::System {
	private:


	public:
		LuaScriptSystem(EngineContext& ctx) : ECS::System(ctx) {}
		~LuaScriptSystem() = default;

	public:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
}
