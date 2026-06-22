#ifndef POTATO_CAMERA_SYSYEM_H
#define POTATO_CAMERA_SYSYEM_H

#include <ecs/system.h>

namespace PotatoEngine::Core::Systems {

	class CameraSystem : public ECS::System {
	public:
		CameraSystem(EngineContext& ctx) : ECS::System(ctx, "Camera System") {}
		~CameraSystem() = default;

	protected:
		void OnStart(std::unique_ptr<ECS::Component> c) override;
		void OnUpdate(std::unique_ptr<ECS::Component> c) override;
		void OnDestroy(std::unique_ptr<ECS::Component> c) override;
	};
}

#endif // POTATO_CAMERA_SYSYEM_H