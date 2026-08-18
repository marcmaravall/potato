#pragma once

#include <core/assets_manager/assets_manager.h>
#include <core/ecs/entity_id.h>
#include <core/logging/debug.h>

#include "assets_manager/asset.h"
#include "commands/command_manager.h"
#include "project.hpp"

namespace PotatoEngine::Editor {

class EditorContext {
private:
public:
    EditorContext() = default;
    ~EditorContext() = default;

public:
    Core::ECS::EntityID SelectedEntity;
    bool IsEntitySelected = false;

    Core::AssetID SelectedAsset = 0;
    bool IsAssetSelected = false;

    CommandManager CManager;
    std::unique_ptr<Project> CurrentProject;

public:
    // This should be called when loading CurrentProject to change engine/editor
    // contexts
    void LoadFromProject(Core::EngineContext& engineContext);

    void SaveFromProject(const Core::EngineContext& engineContext);
};
}  // namespace PotatoEngine::Editor
