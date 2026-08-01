#pragma once

#include <vector>
#include <cstdint>

namespace PotatoEngine::Core::ECS::Components {

class IsometricCell {
    

public:
};

class IsometricGrid {
private:
    std::vector<IsometricCell> m_cells;

public:
    constexpr static size_t DefaultSize = 8;

public:
    size_t Width = DefaultSize;
    size_t Height = DefaultSize;
    size_t Depth = DefaultSize;

public:
    IsometricGrid(size_t width, size_t height, size_t depth) : 
        Width(width), Height(height), Depth(depth) {}
};

} // namespace PotatoEngine::Core::ECS::Components