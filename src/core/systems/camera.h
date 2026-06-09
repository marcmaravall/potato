#ifndef POTATO_CAMERA_SYSYEM_H
#define POTATO_CAMERA_SYSYEM_H

#include <ecs/system.h>

namespace PotatoEngine::Core::Systems {

	class CameraSystem : public ECS::System {
	public:
		CameraSystem(EngineContext& ctx) : ECS::System(ctx, "Camera System") {}
		~CameraSystem() = default;

	public:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
}

#endif // POTATO_CAMERA_SYSYEM_H