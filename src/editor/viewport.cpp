#include "viewport.h"

using namespace PotatoEngine::Core::Rendering;

namespace PotatoEngine::Editor {

    Viewport::Viewport(std::unique_ptr<EditorContext> ctx)
        : EditorPanel("Viewport", std::move(ctx)) {

        m_api = RendererAPI::Create(RendererAPI::Backend::OpenGL);

        FramebufferSpec spec;
        spec.Width = 120;
        spec.Height = 120;

        FramebufferTextureSpec colorAttachment;
        colorAttachment.Format = FramebufferTextureFormat::RGBA8;

        FramebufferTextureSpec entityAttachment;
        entityAttachment.Format = FramebufferTextureFormat::RED_INTEGER;

        FramebufferTextureSpec depthAttachment;
        depthAttachment.Format = FramebufferTextureFormat::Depth;

        spec.Attachments.Attachments = {
            colorAttachment,
            entityAttachment,
            depthAttachment
        };

        m_framebuffer = Framebuffer::Create(spec);

        m_api->SetClearColor(glm::vec4(0.2f, 0.3f, 0.6f, 1.0f));
    }

    void Viewport::OnBegin() {

    }

    void Viewport::OnRender() {
        ImVec2 avail = ImGui::GetContentRegionAvail();

        uint32_t width = (uint32_t)avail.x;
        uint32_t height = (uint32_t)avail.y;

        if (width > 0 && height > 0 &&
            (width != m_width || height != m_height)) {

            m_width = width;
            m_height = height;

            m_framebuffer->Resize(width, height);
        }

        m_framebuffer->Bind();

        m_api->SetViewport(0, 0, m_width, m_height);
        m_api->Clear();

        m_framebuffer->Unbind();

        ImTextureID texId = (ImTextureID)(uintptr_t)m_framebuffer->GetColorAttachmentID(0);

        ImGui::Image(texId, avail, ImVec2(0, 1), ImVec2(1, 0));
    }

    void Viewport::OnEnd() {

    }
}