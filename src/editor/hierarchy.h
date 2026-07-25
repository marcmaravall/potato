#pragma once

#include <core/ecs/components/camera.h>
#include <core/ecs/components/children.h>
#include <core/ecs/components/name.h>
#include <core/ecs/components/parent.h>
#include <core/ecs/components/sprite_renderer.h>
#include <core/ecs/entity_id.h>
#include <core/ecs/systems/sprite_renderer.h>
#include <core/engine_context.h>

#include <format>
#include <stack>

#include "panel.h"

namespace PotatoEngine::Editor {

class HierarchyPanel : public EditorPanel {
private:
    void RenderEntityNode(Core::ECS::EntityID entity, Core::ECS::EntityID&);

public:
    HierarchyPanel(Core::EngineContext& ctx, EditorContext& ectx)
        : EditorPanel("Hierarchy", ctx, ectx) {}

protected:
    void OnBegin() override;
    void OnRender() override;
    void OnEnd() override;
};
}  // namespace PotatoEngine::Editor

