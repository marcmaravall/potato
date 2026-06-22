#ifndef POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H
#define POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H

#include <engine_context.h>
#include <ecs/system.h>

#include <memory>

namespace PotatoEngine::Core::Systems {
	class SpriteRendererSystem : public ECS::System {
	public:
		SpriteRendererSystem(EngineContext& ctx) : ECS::System(ctx, "Sprite Renderer System") {}
		~SpriteRendererSystem() = default;
	
	protected:
		void OnStart(std::unique_ptr<ECS::Component> c) override;
		void OnUpdate(std::unique_ptr<ECS::Component> c) override;
		void OnDestroy(std::unique_ptr<ECS::Component> c) override;
	};
}

#endif // POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H