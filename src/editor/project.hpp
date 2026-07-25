#pragma once

#include <meb.h>

#include <filesystem>
#include <fstream>
#include <istream>
#include <nlohmann/json.hpp>
#include <string>

#include "nlohmann/detail/macro_scope.hpp"

namespace PotatoEngine::Editor {

namespace fs = std::filesystem;

class ProjectSettings {
public:
    std::string ProjectName = "DefaultProject";
    std::string ProjectVersion =
        "1.0.0";  // This is the game version (defined by user)

    std::string EngineVersion = "0.0.1";

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ProjectSettings, ProjectName, ProjectVersion,
                                   EngineVersion)
};

class SceneMeta {
public:
    std::string Name;

    SceneMeta(const std::string& name) : Name(name) {}
};

class Project {
private:
    fs::path m_projectPath;
    ProjectSettings m_projectSettings;
    std::vector<SceneMeta> m_scenes;

public:
    Project() = default;
    ~Project() = default;

    [[nodiscard]] static std::unique_ptr<Project> Load(const std::string &path);

public:
    bool LoadFromFile(const std::string &path);
    bool SaveToFile(const std::string &path);
};

}  // namespace PotatoEngine::Editor
