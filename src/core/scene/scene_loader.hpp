#pragma once

#include <nlohmann/json.hpp>
#include <serialize/serializer.hpp>

#include "engine_context.h"

namespace PotatoEngine::Core {

class SceneLoader {
public:
    void Load(EngineContext& ctx, const std::filesystem::path& file);
};

}  // namespace PotatoEngine::Core
