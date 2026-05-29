#ifndef POTATO_OPENGL_VERTEX_ARRAY_H
#define POTATO_OPENGL_VERTEX_ARRAY_H

#include <glad/glad.h>

#include <ref_scope.h>

#include <rendering/vertex_buffer.h>
#include <rendering/vertex_array.h>

#include <meb.h>

namespace PotatoEngine::Core::Rendering {
	class OpenGL_VertexArray : public VertexArray {
	private:
		GLuint m_id = 0;
		std::vector<Ref<VertexBuffer>> m_vertexBuffers;
		Ref<IndexBuffer> m_indexBuffer;

	public:
		OpenGL_VertexArray() { glGenVertexArrays(1, &m_id); }
		~OpenGL_VertexArray() { glDeleteVertexArrays(1, &m_id); }

		void Bind()  const override { glBindVertexArray(m_id); }
		void Unbind() const override { glBindVertexArray(0); }

		void AddVertexBuffer(const Ref<VertexBuffer>& vb) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& ib) override { m_indexBuffer = ib; }
	
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_vertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_indexBuffer; }
	};
}

#endif // POTATO_OPENGL_VERTEX_ARRAY_H