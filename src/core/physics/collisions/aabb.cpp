#include "aabb.hpp"

namespace PotatoEngine::Core::Physics::Collisions {

AABB_CollisionResult AABB(const AABB_Collision2D &collision) {
    const auto &p1 = collision.P1, s1 = collision.S2;
    const auto &p2 = collision.P2, s2 = collision.S2;

    const float aMinX = p1.x, aMaxX = p1.x + s1.x;
    const float aMinY = p1.y, aMaxY = p1.y + s1.y;
    const float bMinX = p2.x, bMaxX = p2.x + s2.x;
    const float bMinY = p2.y, bMaxY = p2.y + s2.y;

    AABB_CollisionResult result;
    result.Collided = (aMinX <= bMaxX && aMaxX >= bMinX && aMinY <= bMaxY &&
                        aMaxY >= bMinY);
    result.Normal = glm::normalize(glm::vec2(bMinX - aMinX, bMinY - aMinY));
    result.Penetration = glm::vec2(bMaxX - aMinX, bMaxY - aMinY);
    return result;
}

}  // namespace PotatoEngine::Core::Physics::Collisions
