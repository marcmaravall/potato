#include "project.hpp"
#include <filesystem>
#include <fstream>

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

    m_projectSettings = parse["ProjectSettings"];
    
    MEB_LOG_INFOF("Loaded project %s\nProject Version: %s\nEngine Version: %s", 
        m_projectSettings.ProjectName.c_str(),
        m_projectSettings.ProjectVersion.c_str(),
        m_projectSettings.EngineVersion.c_str());
    
    std::vector<std::string> scenes = parse["Scenes"];
    for (auto& scene : scenes) {
        MEB_LOG_INFO(scene.c_str());
    }

    return true;
}

bool Project::SaveToFile(const std::string &path) { return true; }

}  // namespace PotatoEngine::Editor
