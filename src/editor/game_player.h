#pragma once

#include <core/application.h>
#include <core/engine_context.h>
#include <core/executable.h>

#include <thread>

#include "panel.h"

namespace PotatoEngine::Editor {
class GamePlayer : public EditorPanel {
private:
    Core::Application* m_application;

public:
    GamePlayer(Core::EngineContext& ctx, EditorContext& ectx)
        : EditorPanel("Game Player", ctx, ectx) {
        m_application = new Core::Executable(ctx);
    }

    ~GamePlayer() = default;

public:
    void OnBegin() override;
    void OnRender() override;
    void OnEnd() override;
};
};  // namespace PotatoEngine::Editor

