#include "viewport.h"

using namespace PotatoEngine::Core::Rendering;

namespace PotatoEngine::Editor {

    Viewport::Viewport(Core::EngineContext& ctx, EditorContext& ectx) : EditorPanel("Viewport", ctx, ectx) {
        ctx.Renderer.Init();
    }

    void Viewport::OnBegin() {

    }

    void Viewport::OnRender() {
        ImVec2 avail = ImGui::GetContentRegionAvail();
        uint32_t width = (uint32_t)avail.x;
        uint32_t height = (uint32_t)avail.y;

        if (width > 0 && height > 0 && (width != m_width || height != m_height)) {
            m_width = width;
            m_height = height;
			m_engineContext.Renderer.Resize(m_width, m_height);
        }

        m_engineContext.Renderer.BeginScene();
        m_engineContext.Renderer.EndScene();

        ImTextureID texId = (ImTextureID)(uintptr_t)m_engineContext.Renderer.GetFramebuffer().GetColorAttachmentID(0);
        ImGui::Image(texId, avail, ImVec2(0, 1), ImVec2(1, 0));
    }

    void Viewport::OnEnd() {

    }
}