#include "scene_loader.hpp"

#include <fstream>

namespace PotatoEngine::Core {

constexpr static const char* kSceneKey = "scene";

void SceneLoader::Load(EngineContext& ctx, const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) return;

    std::ifstream stream(path);
    nlohmann::json serializer;
    stream >> serializer;

    SceneMeta scene = serializer[kSceneKey];

    ctx.Registry.Clear();
    for (EntityMeta& eMeta : scene.Entities) {
        ECS::EntityID id = eMeta.ID;
        ctx.Registry.CreateEntityWithID(id);
        for (auto& component : eMeta.Components) {
            auto c = Serializer::MetaToComponent(component);
            if (!c) {
                MEB_LOG_ERRORF("Component %s not found",
                               component.Type.c_str());
                continue;
            }
            ctx.Registry.AddComponent(id, std::move(c));
        }
    }
}

}  // namespace PotatoEngine::Core
