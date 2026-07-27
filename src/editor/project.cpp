#include "project.hpp"

#include <filesystem>
#include <fstream>

#include "assets_manager/asset.h"

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

bool Project::SaveToFile(const std::string &path) {
    json save;
    save.emplace("ProjectSettings", _ProjectSettings);
    save.emplace("Scenes", Scenes);
    save.emplace("Assets", Assets);

    std::ofstream stream(path.c_str());
    stream << save.dump(4);
    return true;
}

}  // namespace PotatoEngine::Editor
