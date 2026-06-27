#ifndef POTATO_SYSTEMS_EXAMPLE_H
#define POTATO_SYSTEMS_EXAMPLE_H

#include <ecs/system.h>

namespace PotatoEngine::Core::ECS::Systems {

	class ExampleSystem : public System {
	public:
		ExampleSystem(EngineContext& ctx) : System(ctx) {}
		~ExampleSystem() = default;

	protected:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
}

#endif // POTATO_SYSTEMS_EXAMPLE_H