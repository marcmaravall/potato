#include "physics2d.hpp"

#include <ecs/components/box_collider_2d.h>

#include <ecs/components/rigidbody2d.hpp>

#include "engine_context.h"

namespace PotatoEngine::Core::ECS::Systems {

void Physics2D::OnStart() {}

void Physics2D::OnUpdate() {
    m_context.Registry.Each<Components::Rigidbody2D, Components::Transform>(
        [&](auto& rb, auto& transform) {
            const float dt = m_context.GetDeltaTime();

            rb.Velocity += rb.Mass * rb.GravityForce * m_gravity * dt;
            transform.Position += glm::vec3(rb.Velocity * dt, 0.0);
        });
}

void Physics2D::OnDestroy() {}

}  // namespace PotatoEngine::Core::ECS::Systems
