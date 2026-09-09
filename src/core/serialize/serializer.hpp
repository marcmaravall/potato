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

#include "ecs/registry.h"
#include "meta.hpp"
#include "nlohmann/detail/macro_scope.hpp"

namespace PotatoEngine::Core {
class Serializer {
public:
    static void MetaToEntity(const EntityMeta& meta, Core::ECS::Entity& out,
                             ECS::Registry& registry);
    static std::unique_ptr<Core::ECS::Component> MetaToComponent(
        const ComponentMeta& meta, ECS::Registry& registry);

    static ComponentMeta ComponentToMeta(Core::ECS::Component* component,
                                         ECS::Registry& registry);
};

}  // namespace PotatoEngine::Core
