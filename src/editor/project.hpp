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
#include "nlohmann/detail/macro_scope.hpp"
#include "nlohmann/json_fwd.hpp"

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

// TODO: put all *Meta structs in a better place
struct ComponentMeta {
    std::string Type;
    nlohmann::json Value;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ComponentMeta, Type, Value)
};

struct EntityMeta {
    Core::ECS::EntityID ID;
    std::vector<ComponentMeta> Components;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(EntityMeta, ID, Components)
};

struct SceneMeta {
    std::string Name;
    std::vector<EntityMeta> Entities;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SceneMeta, Name, Entities)
};

struct AssetMeta {
    Core::AssetID ID;
    std::string RelPath;  // assets/RelPath
    std::string Type;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(AssetMeta, ID, RelPath, Type)
};

class Project {
private:
    fs::path m_projectPath;
    ProjectSettings m_projectSettings;
    std::vector<SceneMeta> m_scenes;
    std::vector<AssetMeta> m_assets;

public:
    Project() = default;
    ~Project() = default;

    [[nodiscard]] static std::unique_ptr<Project> Load(const std::string &path);

public:
    bool LoadFromFile(const std::string &path);
    bool SaveToFile(const std::string &path);
};

}  // namespace PotatoEngine::Editor
