#include "camera.h"

#include <engine_context.h>

#include "ecs/components/camera.h"

namespace PotatoEngine::Core::ECS::Systems {
void CameraSystem::OnStart() {}

void CameraSystem::OnUpdate() {
    glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
    int camerasFound = 0;
    m_context.Registry.Each<Components::Camera>([&](auto& camera) {
        color = camera.ClearColor;
        camerasFound++;
    });
    if (camerasFound > 1) {
        MEB_LOG_WARNINGF("Found %d cameras, expected 1", camerasFound);
    } else if (camerasFound == 0) {
        MEB_LOG_WARNING("Found 0 cameras, setting default color to white");
    }
    m_context.Renderer.SetClearColor(color);
}

void CameraSystem::OnDestroy() {}
}  // namespace PotatoEngine::Core::ECS::Systems
