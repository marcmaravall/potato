#include "viewport.h"

using namespace PotatoEngine::Core::Rendering;

namespace PotatoEngine::Editor {

	Viewport::Viewport(std::unique_ptr<EditorContext> ctx) : EditorPanel("Viewport", std::move(ctx)) {
		m_api = Core::Rendering::RendererAPI::Create(Core::Rendering::RendererAPI::Backend::OpenGL);

        FramebufferSpec spec;
        spec.Width  = 120;
        spec.Height = 120;

        m_framebuffer = Framebuffer::Create(spec);
		m_api->SetClearColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
	}

	void Viewport::OnBegin() {

	}

    void Viewport::OnRender() {
        m_framebuffer->Bind();
        m_api->Clear();
        m_api->SetViewport(0, 0, m_width, m_height);
        m_framebuffer->Unbind();

        ImVec2 av = ImGui::GetContentRegionAvail();

        if (av.x != m_width || av.y != m_height) {
            m_framebuffer->Resize((uint32_t)av.x, (uint32_t)av.y);
            m_width = av.x;
            m_height = av.y;
        }

        ImTextureID texId = (ImTextureID)(uintptr_t)m_framebuffer->GetColorAttachmentID();
        ImGui::Image(texId, av, ImVec2(0, 1), ImVec2(1, 0));
    }

	void Viewport::OnEnd() {

	}
}
