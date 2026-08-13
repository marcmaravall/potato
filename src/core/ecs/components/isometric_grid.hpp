#pragma once

#include <vector>
#include <cstdint>

#include <ecs/component.h>
#include <assets_manager/assets_manager.h>

#include <nlohmann/json.hpp>

namespace PotatoEngine::Core::ECS::Components {

struct IsometricCell {
    AssetID TextureRef = 0;

    IsometricCell(AssetID id) : TextureRef(id) {}
    ~IsometricCell() = default;
};

class IsometricGrid : public Component {
private:
    std::vector<IsometricCell> m_cells;

public:
    constexpr static size_t DefaultSize = 8;

public:
    size_t Width = DefaultSize;
    size_t Height = DefaultSize;
    size_t Depth = DefaultSize;

public:
    IsometricGrid() : Component("Isometric Grid") {}
    
    IsometricGrid(size_t width, size_t height, size_t depth) : 
        Component("Isometric Grid"), Width(width), Height(height), Depth(depth) {}
    ~IsometricGrid() = default;

    static constexpr ComponentType StaticType = ComponentType::ISOMETRIC_GRID;
    ComponentType Type() const override { return StaticType; }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(IsometricGrid, Width, Height, Depth)
};

} // namespace PotatoEngine::Core::ECS::Components