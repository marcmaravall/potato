#pragma once

#include <ecs/component.h>
#include <ecs/entity_id.h>

#include <algorithm>
#include <nlohmann/json.hpp>
#include <vector>

#include "nlohmann/detail/macro_scope.hpp"

namespace PotatoEngine::Core::ECS::Components {

class Children : public Component {
public:
    std::vector<EntityID> Value;

public:
    Children() : Component("Children") {}
    Children(std::vector<EntityID> children)
        : Component("Children"), Value(std::move(children)) {}
    ~Children() override = default;

    void Remove(EntityID child) {
        Value.erase(std::remove(Value.begin(), Value.end(), child),
                    Value.end());
    }

    static constexpr ComponentType StaticType = ComponentType::CHILDREN;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Children, Value)
};
}  // namespace PotatoEngine::Core::ECS::Components
