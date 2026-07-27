#include "project.hpp"

#include <filesystem>
#include <fstream>

#include "assets_manager/asset.h"
#include "ecs/entity_id.h"
#include "engine_context.h"

namespace PotatoEngine::Editor {

using json = nlohmann::json;

std::unique_ptr<Project> Project::Load(const std::string &path) {
    std::unique_ptr<Project> project = std::make_unique<Project>();

    if (!project->LoadFromFile(path)) {
        MEB_LOG_ERRORF("Cannot load project from %s", path.c_str());
        return nullptr;
    }

    return std::move(project);
}

bool Project::LoadFromFile(const std::string &path) {
    std::ifstream file(path);

    json parse;
    file >> parse;
    file.close();

    _ProjectSettings = parse["ProjectSettings"];

    MEB_LOG_INFOF("Loaded project %s\nProject Version: %s\nEngine Version: %s",
                  _ProjectSettings.ProjectName.c_str(),
                  _ProjectSettings.ProjectVersion.c_str(),
                  _ProjectSettings.EngineVersion.c_str());

    Scenes = parse["Scenes"];
    _ECS_Meta = parse["ECS_Meta"];
    MEB_LOG_INFOF("ECS CurrentID: %ld", _ECS_Meta.CurrentID);

    MEB_LOG_INFO("SCENES");
    for (auto &scene : Scenes) {
        MEB_LOG_INFO(scene.Name.c_str());
    }

    Assets = parse["Assets"];
    MEB_LOG_INFO("ASSETS:");
    for (auto &asset : Assets) {
        MEB_LOG_INFOF("Asset with relative path '%s' with id: %lld",
                      asset.RelPath.c_str(), asset.ID);
    }

    return true;
}

bool Project::SaveToFile(const std::string &path, Core::EngineContext &ctx) {
    json save;

    save.emplace("ProjectSettings", _ProjectSettings);
    save.emplace("Assets", Assets);

    ECS_Meta ecs;
    ecs.CurrentID = ctx.Registry.GetCurrentID();

    std::queue q = ctx.Registry.GetEmptyQueue();
    ecs.EmptyQueue.clear();
    while (!q.empty()) {
        ecs.EmptyQueue.push_back(q.front());
        q.pop();
    }

    save.emplace("ECS_Meta", ecs);

    json scenes = json::array();

    json scene;
    scene["Name"] = "Scene1";
    scene["Entities"] = json::array();

    auto entities = ctx.Registry.GetEntities();

    for (std::size_t i = 0; i < entities.size(); i++) {
        EntityMeta entity;
        entity.ID = entities[i].first;

        auto components = entities[i].second->GetComponents();

        for (auto *component : components) {
            entity.Components.push_back(Serializer::ComponentToMeta(component));
        }

        scene["Entities"].push_back(entity);
    }

    scenes.push_back(scene);

    save["Scenes"] = scenes;

    std::ofstream stream(path);

    if (!stream.is_open()) return false;

    stream << save.dump(4);

    return true;
}

}  // namespace PotatoEngine::Editor
