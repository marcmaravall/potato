#pragma once

#include <nlohmann/json.hpp>

namespace PotatoEngine::Core::Physics {

struct PhysicsMaterial {
    float Friction = 0.0;
    float Mass = 1.0;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PhysicsMaterial, Friction, Mass)
};

}  // namespace PotatoEngine::Core::Physics
