#pragma once

#include <core/assets_manager/assets_manager.h>
#include <core/ecs/entity_id.h>
#include <core/logging/debug.h>

#include "commands/command_manager.h"
#include "project.hpp"

namespace PotatoEngine::Editor {

class EditorContext {
private:
public:
    EditorContext();
    ~EditorContext();

public:
    Core::ECS::EntityID SelectedEntity;
    bool IsEntitySelected = false;

    CommandManager CManager;
    std::unique_ptr<Project> CurrentProject;

public:
};
}  // namespace PotatoEngine::Editor

