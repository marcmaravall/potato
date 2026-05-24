#include "opengl_framebuffer.h"

using namespace PotatoEngine::Core::Rendering;

void OpenGL_Framebuffer::Invalidate() {
    if (m_fbo) {
        glDeleteFramebuffers(1, &m_fbo);
        glDeleteTextures((GLsizei)m_colorAttachments.size(),
            m_colorAttachments.data());
        glDeleteTextures(1, &m_depthAttachment);
        m_colorAttachments.clear();
        m_depthAttachment = 0;
    }

    glCreateFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    for (uint32_t i = 0; i < m_colorAttachmentSpecs.size(); i++) {
        uint32_t tex;
        glCreateTextures(GL_TEXTURE_2D, 1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        switch (m_colorAttachmentSpecs[i].Format) {
        case FramebufferTextureFormat::RGBA8:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_spec.Width, m_spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            break;
        case FramebufferTextureFormat::RED_INTEGER:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_spec.Width, m_spec.Height, 0, GL_RED_INTEGER, GL_INT, nullptr);
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex, 0);
        m_colorAttachments.push_back(tex);
    }

    if (m_depthAttachmentSpec.Format != FramebufferTextureFormat::None) {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_spec.Width, m_spec.Height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);
    }

    if (m_colorAttachments.size() > 1) {
        GLenum buffers[4] = {
            GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3
        };
        glDrawBuffers((GLsizei)m_colorAttachments.size(), buffers);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
