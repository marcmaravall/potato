#ifndef POTATO_SYSTEMS_EXAMPLE_H
#define POTATO_SYSTEMS_EXAMPLE_H

#include <ecs/system.h>

namespace PotatoEngine::Core::Systems {

	class ExampleSystem : public ECS::System {
	public:
		ExampleSystem(EngineContext& ctx) : System(ctx, "Example System") {}
		~ExampleSystem() = default;

	protected:
		void OnStart(std::unique_ptr<ECS::Component> c) override;
		void OnUpdate(std::unique_ptr<ECS::Component> c) override;
		void OnDestroy(std::unique_ptr<ECS::Component> c) override;
	};
}

#endif // POTATO_SYSTEMS_EXAMPLE_H