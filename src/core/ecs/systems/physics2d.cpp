#include "physics2d.hpp"

#include <ecs/components/box_collider_2d.h>

#include <ecs/components/rigidbody2d.hpp>

#include "engine_context.h"

#include <physics/collisions/aabb.hpp>

namespace PotatoEngine::Core::ECS::Systems {

using namespace Physics::Collisions;

void Physics2D::OnStart() {}

void Physics2D::OnUpdate() {
    struct Entry {
        EntityID Entity;
        Components::Transform& Transform;
        Components::BoxCollider2D& Collider;
    };

    std::vector<Entry> entries;
    // for ALL rigidbodies and transforms
    m_context.Registry.Each<Components::Rigidbody2D, Components::Transform>(
        [&](auto& rb, auto& transform) {
            const float dt = m_context.GetDeltaTime();

            rb.Velocity += rb.Mass * rb.GravityForce * m_gravity * dt;
            transform.Position += glm::vec3(rb.Velocity * dt, 0.0);
        });

    // aabb collisions
    m_context.Registry.EachWithID<Components::Transform, Components::BoxCollider2D>(
        [&](EntityID id, auto& transform, auto& collider) {
            entries.push_back(Entry{id, transform, collider});
        });

    using namespace Components;

    const size_t count = entries.size();
    // this is a very basic O(n^2) collision detection and resolution
    // in the future this should be improved a lot
    for (size_t i = 0; i < count; i++) {
        for (size_t j = i + 1; j < count; j++) {
            auto& a = entries[i];
            auto& b = entries[j];
            AABB_Collision2D collision = AABB_Collision2D(
                static_cast<glm::vec2>(a.Transform.Position) + a.Collider.Origin, a.Collider.Size,
                static_cast<glm::vec2>(b.Transform.Position) + b.Collider.Origin, b.Collider.Size
            );
            const auto result = Physics::Collisions::AABB(collision);
            Rigidbody2D* rbA = m_context.Registry.TryGetComponent<Rigidbody2D>(a.Entity);
            Rigidbody2D* rbB = m_context.Registry.TryGetComponent<Rigidbody2D>(b.Entity);
            if (result.Collided) {
                if (rbA) {
                    rbA->Velocity -= glm::vec2(
                        result.Normal * glm::dot(rbA->Velocity, result.Normal));
                }
                if (rbB) {
                    rbB->Velocity -= glm::vec2(
                        result.Normal * glm::dot(rbB->Velocity, result.Normal));
                }

                glm::vec2 correction = result.Normal * result.Penetration*0.0001f;
                if (rbA && rbB) {
                    correction /= 2.0f;
                }
                if (rbA) {
                    a.Transform.Position -= glm::vec3(correction, 0.0f);
                }
                if (rbB) {
                    b.Transform.Position += glm::vec3(correction, 0.0f);
                }
            }
        }
    }
}

void Physics2D::OnDestroy() {}

}  // namespace PotatoEngine::Core::ECS::Systems
