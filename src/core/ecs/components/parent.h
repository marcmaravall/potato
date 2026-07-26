#pragma once

#include <ecs/component.h>
#include <ecs/entity_id.h>

#include <nlohmann/json.hpp>

#include "nlohmann/detail/macro_scope.hpp"

namespace PotatoEngine::Core::ECS::Components {

class Parent : public Component {
public:
    EntityID Value;

public:
    Parent() : Component("Parent") {}
    Parent(EntityID parent) : Component("Parent"), Value(parent) {}
    ~Parent() override = default;

    static constexpr ComponentType StaticType = ComponentType::PARENT;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Parent, Value)
};
}  // namespace PotatoEngine::Core::ECS::Components
