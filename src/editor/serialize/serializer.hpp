#pragma once

#include <core/ecs/components/all_components.h>
#include <core/engine_context.h>
#include <meb.h>

#include <fstream>
#include <glm/glm.hpp>
#include <istream>

#include "nlohmann/detail/macro_scope.hpp"

namespace PotatoEngine::Editor {

class Serializer {
private:
public:
    static void LoadFromFile(Core::EngineContext& ctx, const std::string& path);
    static void SaveToFile(const Core::EngineContext& ctx,
                           const std::string& path);
};

}  // namespace PotatoEngine::Editor

// Define types to nlohmann::json
namespace glm {
// glm:
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec4, x, y, z, w)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec3, x, y, z)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec2, x, y)

}  // namespace glm
