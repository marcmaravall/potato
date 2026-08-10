#include "engine_context.h"

#include <assets_manager/assets/lua_script_asset.h>
#include <core/rendering/renderer2d.h>
#include <ecs/components/lua_script.h>
#include <ecs/components/name.h>
#include <ecs/components/transform.h>
#include <ecs/systems/camera.h>
#include <ecs/systems/example.h>
#include <ecs/systems/sprite_renderer.h>

#include <ecs/components/isometric_grid.hpp>

#include "ecs/entity_id.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace PotatoEngine::Core {
using namespace ECS;
EngineContext::EngineContext() : Renderer(*this) {}

EngineContext::~EngineContext() { Debug.Log("Engine context destroyed."); }

void EngineContext::Start() {
    RegisterComponents();

    Registry.AddSystem<ECS::Systems::CameraSystem>(*this);
    Registry.AddSystem<ECS::Systems::SpriteRendererSystem>(*this);
    Registry.AddSystem<ECS::Systems::LuaScriptSystem>(*this);

    _AssetManager.ScanAssets();
}

void EngineContext::RegisterComponents() {
    using namespace ECS::Components;

    Registry.RegisterComponent<Camera>();
    Registry.RegisterComponent<Children>();
    Registry.RegisterComponent<LuaScript>();
    Registry.RegisterComponent<Name>();
    Registry.RegisterComponent<Parent>();
    Registry.RegisterComponent<SpriteRenderer>();
    Registry.RegisterComponent<Transform>();
}

EntityID EngineContext::GetMainCameraEntity() {
    this->Registry.ForEachComponentOfType<Components::Camera>(
        [&](EntityID id, Components::Camera& camera) { return id; });

    return NULL_ENTITY;
}

glm::mat4 EngineContext::GetViewProjectionMatrix() {
    EntityID mainCamera = GetMainCameraEntity();
    if (mainCamera == NULL_ENTITY) {
        return glm::identity<glm::mat4>();
    }

    auto* component = Registry.TryGetComponent<Components::Camera>(mainCamera);
    auto* transform =
        Registry.TryGetComponent<Components::Transform>(mainCamera);
    if (!component || !transform) return glm::mat4(1.0f);

    glm::mat4 res = glm::translate(glm::mat4(1.0f), -transform->Position) *
                    glm::scale(glm::mat4(1.0f), glm::vec3(component->Zoom)) *
                    glm::mat4(1.0f);
    return res;
}

}  // namespace PotatoEngine::Core
