#ifndef POTATO_OPENGL_VERTEX_BUFFER_H
#define POTATO_OPENGL_VERTEX_BUFFER_H

#include <ref_scope.h>

#include <cstdint>

#include <glad/glad.h>
#include <rendering/vertex_buffer.h>
#include <rendering/buffer_layout.h>

namespace PotatoEngine::Core::Rendering {
	class OpenGL_VertexBuffer : public VertexBuffer {
    private:
        GLuint m_id = 0;
		BufferLayout m_layout;

    public:
        OpenGL_VertexBuffer(uint32_t size) {
			glGenBuffers(1, &m_id);
            
        }

        OpenGL_VertexBuffer(float* vertices, uint32_t size) {
			glGenBuffers(1, &m_id);
        }

        ~OpenGL_VertexBuffer() {
			glDeleteBuffers(1, &m_id);
        }

        void Bind() const override { glBindBuffer(GL_ARRAY_BUFFER, m_id); }
        void Unbind() const override { glBindBuffer(GL_ARRAY_BUFFER, 0); }

        void SetData(const void* data, uint32_t size) override {
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        }

		const BufferLayout& GetLayout() const override { return m_layout; }
        void SetLayout(const BufferLayout& layout) override { m_layout = layout; }
	};
}

#endif // POTATO_OPENGL_VERTEX_BUFFER_H