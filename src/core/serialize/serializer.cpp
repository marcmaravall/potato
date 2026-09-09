#include "serializer.hpp"

#include <memory>

#include "ecs/components/all_components.h"
#include "ecs/components/box_collider_2d.h"
#include "ecs/components/circle_collider_2d.hpp"
#include "ecs/components/rigidbody2d.hpp"
#include "ecs/registry.h"

namespace PotatoEngine::Core {

using namespace Core::ECS;
using namespace Core::ECS::Components;

using json = nlohmann::json;

template <typename T>
std::unique_ptr<Component> DeserializeComponent(const nlohmann::json &j) {
    auto c = std::make_unique<T>();
    j.get_to(*c);
    return c;
}

std::unique_ptr<Component> Serializer::MetaToComponent(
    const ComponentMeta &component, ECS::Registry &registry) {
    return registry.DeserializeComponent(component);
}

void Serializer::MetaToEntity(const EntityMeta &meta, Entity &out,
                              ECS::Registry &registry) {
    for (auto &component : meta.Components) {
        out.Add(std::move(MetaToComponent(component, registry)));
    }
}

// TODO: do in a  better way
ComponentMeta Serializer::ComponentToMeta(Core::ECS::Component *component,
                                          ECS::Registry &registry) {
    return registry.SerializeComponent(component);
}

}  // namespace PotatoEngine::Core
