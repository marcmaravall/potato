#include "editor_context.h"

#include <core/engine_context.h>
#include <portable-file-dialogs/portable-file-dialogs.h>

#include "ecs/entity.h"
#include "serialize/serializer.hpp"

namespace PotatoEngine::Editor {

using namespace Core;

void EditorContext::UserOpenProject(EngineContext& ctx) {
    auto dialog = pfd::open_file("Choose project to open", pfd::path::home(),
                                 {"JSON Files", "*.json", "All Files", "*"},
                                 pfd::opt::multiselect);

    auto files = dialog.result();

    if (!files.empty()) {
        const std::filesystem::path& p = files[0];
        MEB_LOG_INFOF("Open project from directory %s",
                      p.parent_path().c_str());
        ctx._AssetManager.SetRoot(p.parent_path());
        ctx._AssetManager.ScanAssets();

        CurrentProject = Project::Load(p.c_str());
        LoadFromProject(ctx);
        MEB_LOG_INFO("Loaded project successfully!");
    }
}

void EditorContext::UserSaveProject(Core::EngineContext& ctx) {
    auto dialog = pfd::save_file("Save project", pfd::path::home(),
                                 {"JSON Files", "*.json", "All Files", "*"});
    auto file = dialog.result();

    if (!file.empty()) {
        CurrentProject->SaveToFile(file, ctx);
    }
}

void EditorContext::LoadFromProject(EngineContext& engineContext) {
    if (!CurrentProject) {
        MEB_LOG_ERROR("CurrentProject is nullptr!");
        return;
    }
    if (CurrentProject->Scenes.size() < 1) {
        MEB_LOG_ERROR("CurrentProject has no scenes!");
        return;
    }

    engineContext.Registry.Clear();

    engineContext.Registry.SetCurrentID(CurrentProject->_ECS_Meta.CurrentID);
    auto& queue = engineContext.Registry.GetEmptyQueue();
    auto& vec = CurrentProject->_ECS_Meta.EmptyQueue;
    for (ECS::EntityID id : vec) {
        queue.push(id);
    }

    std::size_t scene = 0;
    for (EntityMeta& eMeta : CurrentProject->Scenes[scene].Entities) {
        ECS::EntityID id = eMeta.ID;
        engineContext.Registry.CreateEntityWithID(id);
        for (auto& component : eMeta.Components) {
            auto c = Serializer::MetaToComponent(component);
            if (!c) {
                MEB_LOG_ERRORF("Component %s not found",
                               component.Type.c_str());
                continue;
            }
            engineContext.Registry.AddComponent(id, std::move(c));
        }
    }
}

void EditorContext::SaveFromProject(const EngineContext& engineContext) {}

}  // namespace PotatoEngine::Editor
