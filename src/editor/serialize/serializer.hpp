#pragma once

#include <core/ecs/component.h>
#include <core/ecs/components/all_components.h>
#include <core/ecs/entity.h>
#include <core/ecs/entity_id.h>
#include <core/engine_context.h>
#include <meb.h>

#include <fstream>
#include <glm/glm.hpp>
#include <istream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace PotatoEngine::Editor {

struct ComponentMeta {
    std::string Type;
    nlohmann::json Value;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ComponentMeta, Type, Value)
};

struct EntityMeta {
    Core::ECS::EntityID ID;
    std::vector<ComponentMeta> Components;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EntityMeta, ID, Components)
};

struct SceneMeta {
    std::string Name;
    std::vector<EntityMeta> Entities;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneMeta, Name, Entities)
};

struct AssetMeta {
    Core::AssetID ID;
    std::string RelPath;  // assets/RelPath
    std::string Type;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(AssetMeta, ID, RelPath, Type)
};

class Serializer {
private:
public:
    static void LoadFromFile(Core::EngineContext& ctx, const std::string& path);
    static void SaveToFile(const Core::EngineContext& ctx,
                           const std::string& path);

    static void MetaToEntity(const EntityMeta& meta, Core::ECS::Entity& out);
    static std::unique_ptr<Core::ECS::Component> MetaToComponent(
        const ComponentMeta& meta);
};

}  // namespace PotatoEngine::Editor

// Define types to nlohmann::json
namespace glm {
// glm:
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec4, x, y, z, w)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec3, x, y, z)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec2, x, y)

}  // namespace glm
