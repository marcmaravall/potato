#ifndef POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H
#define POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H

#include <engine_context.h>
#include <ecs/system.h>

#include <memory>

namespace PotatoEngine::Core::Systems {
	class SpriteRendererSystem : public ECS::System {
	public:
		SpriteRendererSystem(EngineContext& ctx) : ECS::System(ctx) {}
		~SpriteRendererSystem() = default;
	
	protected:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
}

#endif // POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H