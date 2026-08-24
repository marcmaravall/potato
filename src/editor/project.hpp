#pragma once

#include <assets_manager/assets_manager.h>
#include <meb.h>

#include <filesystem>
#include <fstream>
#include <istream>
#include <nlohmann/json.hpp>
#include <string>

#include "assets_manager/asset.h"
#include "ecs/entity_id.h"
#include "engine_context.h"
#include "nlohmann/detail/macro_scope.hpp"
#include "nlohmann/json_fwd.hpp"
#include "serialize/serializer.hpp"

namespace PotatoEngine::Editor {

class EditorContext;

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

// TODO: put all *Meta structs in a better place
class Project {
public:
    fs::path ProjectPath;
    ProjectSettings _ProjectSettings;
    std::vector<Core::SceneMeta> Scenes;
    Core::ECS_Meta _ECS_Meta;

public:
    Project() = default;
    ~Project() = default;

    [[nodiscard]] static std::unique_ptr<Project> Load(const std::string &path);

public:
    bool LoadFromFile(const std::string &path);
    bool SaveToFile(const std::string &path, Core::EngineContext &ctx);
};

}  // namespace PotatoEngine::Editor
