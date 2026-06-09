#ifndef POTATO_SYSTEMS_EXAMPLE_H
#define POTATO_SYSTEMS_EXAMPLE_H

#include <ecs/system.h>

namespace PotatoEngine::Core::Systems {

	class ExampleSystem : public ECS::System {
	public:
		ExampleSystem(EngineContext& ctx) : System(ctx, "Example System") {}
		~ExampleSystem() = default;

	public:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
}

#endif // POTATO_SYSTEMS_EXAMPLE_H