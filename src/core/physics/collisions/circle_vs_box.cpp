#include "circle_vs_box.hpp"

namespace PotatoEngine::Core::Physics::Collisions {

CircleVsBoxCollisionInfo CircleVsBox(glm::vec3 circle, glm::vec4 rect) {
    const float radius = circle.z;

    const float width = rect.z;
    const float height = rect.w;

    const float closestX = std::max(rect.x, std::min(circle.x, rect.x + width));
    const float closestY =
        std::max(rect.y, std::min(circle.y, rect.y + height));
    const float dstX = circle.x - closestX;
    const float dstY = circle.y - closestY;

    CircleVsBoxCollisionInfo cvb;
    cvb.Collide = (dstX * dstX + dstY * dstY) < radius * radius;
    return cvb;
}

}  // namespace PotatoEngine::Core::Physics::Collisions
