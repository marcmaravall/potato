#pragma once

#include <string>

namespace PotatoEngine::Core::ECS {

enum class ComponentType {
    BOX_COLLIDER_2D,
    CAMERA,
    CHILDREN,
    LUA_SCRIPT,
    NAME,
    PARENT,
    SPRITE_RENDERER,
    TRANSFORM,
    ISOMETRIC_GRID,
};

class Component {
public:
    std::string Name = "[DEFAULT_COMPONENT]";

public:
    Component() = default;
    Component(const std::string& name) : Name(name) {}
    virtual ~Component() = default;

    [[nodiscard]]
    virtual ComponentType Type() const = 0;
};
}  // namespace PotatoEngine::Core::ECS
