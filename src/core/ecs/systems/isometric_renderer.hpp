#pragma once

#include <ecs/system.h>
#include <ecs/components/isometric_grid.hpp>

#include <ecs/entity_id.h>

namespace PotatoEngine::Core::ECS::Systems {

class IsometricRenderer : public System {
public:
    IsometricRenderer(EngineContext& ctx) : System(ctx) {}
    ~IsometricRenderer() = default;

public:
    void OnStart() override;
    void OnUpdate() override;
    void OnDestroy() override;
};

}  // namespace PotatoEngine::Core::ECS::Systems