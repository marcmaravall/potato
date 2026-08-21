#pragma once

#include <glad/glad.h>

#include "application.h"
#include "engine_context.h"
#include "windowing/window.h"

namespace PotatoEngine::Core {

class Game : public Application {
private:
    std::unique_ptr<Windowing::Window> m_window = nullptr;
    EngineContext m_engineContext;

public:
    Game();
    ~Game() = default;

    void OnStart() override;
    void OnUpdate() override;
    void OnDestroy() override;
};

}  // namespace PotatoEngine::Core
