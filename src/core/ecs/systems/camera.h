#ifndef POTATO_CAMERA_SYSYEM_H
#define POTATO_CAMERA_SYSYEM_H

#include <ecs/system.h>
#include <meb.h>

namespace PotatoEngine::Core::ECS::Systems {

class CameraSystem : public System {
public:
    CameraSystem(EngineContext& ctx) : System(ctx) {}
    ~CameraSystem() = default;

protected:
    void OnStart() override;
    void OnUpdate() override;
    void OnDestroy() override;
};
}  // namespace PotatoEngine::Core::ECS::Systems

#endif  // POTATO_CAMERA_SYSYEM_H
