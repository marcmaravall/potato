#pragma once

#include "panel.h"
#include <imgui.h>

namespace PotatoEngine::Editor {

// this is NOT the profiler for the game
class Profiler : public EditorPanel {
public:
    Profiler(Core::EngineContext& ctx, EditorContext& ectx)
        : EditorPanel("Profiler", ctx, ectx) {}
    ~Profiler() = default;

public:
    void OnBegin();
    void OnRender();
    void OnEnd();

private:
    static constexpr int kSize = 400;
    float m_fps[kSize] = {};
    int m_offset = 0;
};

}  // namespace PotatoEngine::Editor