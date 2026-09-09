#pragma once

#include <ecs/entity_id.h>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace PotatoEngine::Core {

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

struct ECS_Meta {
    Core::ECS::EntityID CurrentID;
    std::vector<Core::ECS::EntityID> EmptyQueue;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ECS_Meta, CurrentID, EmptyQueue)
};

struct SceneMeta {
    std::string Name;
    std::vector<EntityMeta> Entities;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneMeta, Name, Entities)
};

}  // namespace PotatoEngine::Core

// Define types to nlohmann::json
namespace glm {
// glm:
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec4, x, y, z, w)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec3, x, y, z)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(glm::vec2, x, y)

}  // namespace glm
