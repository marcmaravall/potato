#ifndef POTATO_VERTEX_ARRAY_H
#define POTATO_VERTEX_ARRAY_H

#include <vector>

#include "vertex_buffer.h"
#include "index_buffer.h"

namespace PotatoEngine::Core::Rendering {

	class VertexArray {
	public:
		virtual ~VertexArray() = default;
	
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Scope<VertexArray> Create();
	};
};

#endif // POTATO_RENDERING_VERTEX_ARRAY_H