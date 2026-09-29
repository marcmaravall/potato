#include "editor_context.h"

#include <core/engine_context.h>
#include <portable-file-dialogs/portable-file-dialogs.h>

#include "ecs/entity.h"
#include "file_listener.hpp"
#include "serialize/serializer.hpp"

namespace PotatoEngine::Editor {

using namespace Core;

void EditorContext::OpenScene(EngineContext& engineContext,
                              const SceneMeta& sceneMeta) {
    engineContext.Registry.Clear();
    for (const EntityMeta& eMeta : sceneMeta.Entities) {
        ECS::EntityID id = eMeta.ID;
        engineContext.Registry.CreateEntityWithID(id);
        for (auto& component : eMeta.Components) {
            auto c =
                Serializer::MetaToComponent(component, engineContext.Registry);
            if (!c) {
                MEB_LOG_ERRORF("Component %s not found",
                               component.Type.c_str());
                continue;
            }
            engineContext.Registry.AddComponent(id, std::move(c));
        }
    }
}

void EditorContext::UserOpenProject(EngineContext& ctx) {
    auto dialog = pfd::open_file("Choose project to open", pfd::path::home(),
                                 {"JSON Files", "*.json", "All Files", "*"},
                                 pfd::opt::multiselect);

    auto files = dialog.result();

    if (!files.empty()) {
        const std::filesystem::path& p = files[0];
        MEB_LOG_INFOF("Open project from directory %s",
                      p.parent_path().string().c_str());
        ctx._AssetManager.SetRoot(p.parent_path());
        ctx._AssetManager.ScanAssets();

        m_fileWatcher.stop();
        m_fileWatcher.add_listener(p.parent_path(), new FileListener(ctx));
        m_fileWatcher.watch();

        CurrentProject = Project::Load(p.string().c_str());
        LoadFromProject(ctx);
        MEB_LOG_INFO("Loaded project successfully!");
    }
}

void EditorContext::UserSaveProject(Core::EngineContext& ctx) {
    auto dialog = pfd::save_file("Save project", pfd::path::home(),
                                 {"JSON Files", "*.json", "All Files", "*"});
    auto file = dialog.result();

    if (!file.empty()) {
        CurrentProject->SaveToFile(file.c_str(), ctx);
    }
}

void EditorContext::LoadFromProject(EngineContext& engineContext) {
    if (!CurrentProject) {
        MEB_LOG_ERROR("CurrentProject is nullptr!");
        return;
    }

    engineContext.Registry.Clear();
}

void EditorContext::SaveFromProject(const EngineContext& engineContext) {}

}  // namespace PotatoEngine::Editor
