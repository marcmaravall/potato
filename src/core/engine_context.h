#ifndef POTATO_ENGINE_H
#define POTATO_ENGINE_H

#include <assets_manager/assets_manager.h>
#include <ecs/component.h>
#include <ecs/components/camera.h>
#include <ecs/entity.h>
#include <ecs/registry.h>
#include <ecs/system.h>
#include <ecs/systems/lua_script_system.h>
#include <input/input_state.h>
#include <logging/debug.h>
#include <rendering/renderer2d.h>

#include <iostream>
#include <sol/sol.hpp>
#include <vector>

#include "ecs/entity_id.h"

namespace PotatoEngine::Core {

namespace Systems {
class CameraSystem;
}

class EngineContext {
private:
    double m_dt = 1.0 / 60.0;
    double m_time = 0.0;

public:
    bool IsRunning = false;

    ECS::Registry Registry;
    AssetManager _AssetManager;
    Logging::Debug Debug;
    Rendering::Renderer2D Renderer;
    Input::InputState InputState;

public:
    // This should be assigned once per frame
    void SetDeltaTime(double dt) {
        m_dt = dt;
        m_time += dt;
    }
    double GetDeltaTime() { return m_dt; }
    double GetTime() { return m_time; }

public:
    sol::state& GetLuaState() {
        return Registry.GetSystem<ECS::Systems::LuaScriptSystem>()
            .GetLuaState();
    }

    ECS::EntityID GetMainCameraEntity();

    glm::mat4 GetViewProjectionMatrix();

    EngineContext();
    ~EngineContext();

    void RegisterComponents();

    void Start();
};
}  // namespace PotatoEngine::Core

#endif  // POTATO_ENGINE_H
