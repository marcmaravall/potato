#ifndef POTATO_OPENGL_FRAMEBUFFER_H
#define POTATO_OPENGL_FRAMEBUFFER_H

#include <glad/glad.h>
#include <rendering/framebuffer.h>

#include <vector>

namespace PotatoEngine::Core::Rendering {

	class OpenGL_Framebuffer : public Framebuffer {
	private:
		FramebufferSpec m_spec;
		GLuint m_fbo = 0;

		std::vector<FramebufferTextureSpec> m_colorAttachmentSpecs;
		FramebufferTextureSpec m_depthAttachmentSpec;

		std::vector<uint32_t> m_colorAttachments;
		uint32_t m_depthAttachment = 0;

	private:
		void Invalidate();

	public:
		OpenGL_Framebuffer(const FramebufferSpec& spec)
			: m_spec(spec), m_fbo(0), m_depthAttachment(0) {

			for (auto& attachment : spec.Attachments.Attachments) {
				if (attachment.Format == FramebufferTextureFormat::DEPTH24STENCIL8)
					m_depthAttachmentSpec = attachment;
				else
					m_colorAttachmentSpecs.push_back(attachment);
			}

			Invalidate();
		}

		~OpenGL_Framebuffer() {
			glDeleteFramebuffers(1, &m_fbo);
			glDeleteTextures((GLsizei)m_colorAttachments.size(), m_colorAttachments.data());
			glDeleteTextures(1, &m_depthAttachment);
		}

	public:
		GLenum ToGLInternalFormat(FramebufferTextureFormat format) {
			switch (format) {
			case FramebufferTextureFormat::RGBA8:
				return GL_RGBA8;

			case FramebufferTextureFormat::RED_INTEGER:
				return GL_R32I;

			case FramebufferTextureFormat::DEPTH24STENCIL8:
				return GL_DEPTH24_STENCIL8;
			}

			return 0;
		}

		GLenum ToGLDataFormat(FramebufferTextureFormat format) {
			switch (format) {
			case FramebufferTextureFormat::RGBA8:
				return GL_RGBA;

			case FramebufferTextureFormat::RED_INTEGER:
				return GL_RED_INTEGER;
			}

			return 0;
		}

	public:
		void Bind() override {
			glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			glViewport(0, 0, m_spec.Width, m_spec.Height);
		}

		void Unbind() override {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Resize(uint32_t width, uint32_t height) override {
			m_spec.Width = width;
			m_spec.Height = height;
			Invalidate();
		}

		int ReadPixel(uint32_t attachmentIndex, int x, int y) override {
			glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
			int pixel;
			glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixel);
			return pixel;
		}

		void ClearAttachment(uint32_t attachmentIndex, int value) override {
			auto& spec = m_colorAttachmentSpecs[attachmentIndex];
			glClearTexImage(m_colorAttachments[attachmentIndex], 0, ToGLDataFormat(spec.Format), GL_INT, &value);
		}

		uint32_t GetColorAttachmentID(uint32_t index = 0) const override {
			assert(index < m_colorAttachments.size() && "Index out of bounds!");

			return m_colorAttachments[index];
		}

		const FramebufferSpec& GetSpec() const override { return m_spec; }
	};
}

#endif // POTATO_OPENGL_FRAMEBUFFER_H