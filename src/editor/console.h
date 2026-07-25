#pragma once

#include <core/engine_context.h>
#include <platform/api.h>

#include <memory>

#include "core/logging/debug.h"
#include "panel.h"

namespace PotatoEngine::Editor {

class Console : public EditorPanel {
public:
    Console(Core::EngineContext& ctx, EditorContext& ectx)
        : EditorPanel("Console", ctx, ectx) {}

protected:
    void OnBegin() override;
    void OnRender() override;
    void OnEnd() override;
};
}  // namespace PotatoEngine::Editor
