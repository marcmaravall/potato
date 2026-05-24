#ifndef POTATO_OPENGL_VERTEX_BUFFER_H
#define POTATO_OPENGL_VERTEX_BUFFER_H

#include <ref_scope.h>
#include <rendering/vertex_buffer.h>

namespace PotatoEngine::Core::Rendering {
	class OpenGL_VertexBuffer : public VertexBuffer {
	public:
        ~OpenGL_VertexBuffer() = default;

        void Bind() override;
        void Unbind() override;

        void SetData(const void* data, uint32_t size) override;

        const BufferLayout& GetLayout() const = 0;
        void SetLayout(const BufferLayout& layout) = 0;

        Ref<VertexBuffer> Create(uint32_t size);
        Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};
}

#endif // POTATO_OPENGL_VERTEX_BUFFER_H