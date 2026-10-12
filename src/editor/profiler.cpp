#include "profiler.hpp"

#include <imgui.h>
#include <implot/implot.h>

namespace PotatoEngine::Editor {

void Profiler::OnBegin() {}

void Profiler::OnRender() {
    const float fps = ImGui::GetIO().Framerate;

    m_fps[m_offset] = fps;
    m_offset = (m_offset + 1) % kSize;

    ImGui::Text("FPS: %.1f", fps);

    if (ImPlot::BeginPlot("FPS", ImVec2(-1, 150))) {
        ImPlot::SetupAxes("Time", "FPS", ImPlotAxisFlags_NoTickLabels,
                          ImPlotAxisFlags_AutoFit);
        ImPlot::PlotLine("FPS", m_fps, kSize, 1.0, 0.0, ImPlotSpec(ImPlotProp_Offset, m_offset));
        ImPlot::EndPlot();
    }

    // TODO: add more profiling data
}

void Profiler::OnEnd() {}

}  // namespace PotatoEngine::Editor