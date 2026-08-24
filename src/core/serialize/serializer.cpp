#include "serializer.hpp"

#include <memory>

#include "ecs/components/all_components.h"

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
    const ComponentMeta &component) {
    if (component.Type == "Name")
        return DeserializeComponent<Name>(component.Value);

    // if (component.Type == "BoxCollider2D")
    //    return DeserializeComponent<BoxCollider2D>(component.Value);

    if (component.Type == "Camera")
        return DeserializeComponent<Camera>(component.Value);

    if (component.Type == "Children")
        return DeserializeComponent<Children>(component.Value);

    if (component.Type == "LuaScript")
        return DeserializeComponent<LuaScript>(component.Value);

    if (component.Type == "Parent")
        return DeserializeComponent<Parent>(component.Value);

    if (component.Type == "SpriteRenderer")
        return DeserializeComponent<SpriteRenderer>(component.Value);

    if (component.Type == "Transform")
        return DeserializeComponent<Transform>(component.Value);
    if (component.Type == "IsometricGrid")
        return DeserializeComponent<IsometricGrid>(component.Value);

    return nullptr;
}

void Serializer::MetaToEntity(const EntityMeta &meta, Entity &out) {
    for (auto &component : meta.Components) {
        out.Add(std::move(MetaToComponent(component)));
    }
}

// TODO: do in a  better way
ComponentMeta Serializer::ComponentToMeta(Core::ECS::Component *component) {
    ComponentMeta res;

    if (auto c = dynamic_cast<Name *>(component)) {
        res.Type = "Name";
        res.Value = *c;
    } else if (auto c = dynamic_cast<Camera *>(component)) {
        res.Type = "Camera";
        res.Value = *c;
    } else if (auto c = dynamic_cast<Children *>(component)) {
        res.Type = "Children";
        res.Value = *c;
    } else if (auto c = dynamic_cast<LuaScript *>(component)) {
        res.Type = "LuaScript";
        res.Value = *c;
    } else if (auto c = dynamic_cast<Parent *>(component)) {
        res.Type = "Parent";
        res.Value = *c;
    } else if (auto c = dynamic_cast<SpriteRenderer *>(component)) {
        res.Type = "SpriteRenderer";
        res.Value = *c;
    } else if (auto c = dynamic_cast<Transform *>(component)) {
        res.Type = "Transform";
        res.Value = *c;
    } else if (auto c = dynamic_cast<IsometricGrid *>(component)) {
        res.Type = "IsometricGrid";
        res.Value = *c;
    } else {
        res.Type = "NULL";
        res.Value = nullptr;
    }

    return res;
}

// DEPRECATED:
// Tests:
void Serializer::LoadFromFile(Core::EngineContext &ctx,
                              const std::string &path) {
    std::ifstream file(path);
    if (file.is_open()) {
        json load = json::parse(file);

        std::string name = load.at("project");
        std::string version = load.at("version");
        MEB_LOG_INFOF("Project: %s. Version: %s", name.c_str(),
                      version.c_str());

    } else {
        MEB_LOG_ERROR("File to load not found!");
    }
}

void Serializer::SaveToFile(const Core::EngineContext &ctx,
                            const std::string &path) {
    json save = {{"project", "test_project"}, {"version", "0.0.1"}};

    std::ofstream file(path);
    file << save.dump(4);
    file.close();

    MEB_LOG_INFOF("Saved context to %s", path.c_str());
}
// ----

}  // namespace PotatoEngine::Core
