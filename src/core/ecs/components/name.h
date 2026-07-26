#pragma once

#include <ecs/component.h>

#include <string>

namespace PotatoEngine::Core::ECS::Components {

class Name : public Component {
public:
    std::string Value = "";

public:
    Name() : Component("Name") {}
    Name(std::string str) : Component("Name"), Value(std::move(str)) {}
    ~Name() override = default;

    static constexpr ComponentType StaticType = ComponentType::NAME;
    ComponentType Type() const override { return StaticType; }
};
}  // namespace PotatoEngine::Core::ECS::Components
