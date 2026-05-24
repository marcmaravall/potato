#ifndef POTATO_VERTEX_ARRAY_H
#define POTATO_VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "index_buffer.h"

namespace PotatoEngine::Core::Rendering {

	class VertexArray {
	public:
		virtual ~VertexArray() = 0;
	
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) = 0;
	};
};

#endif // POTATO_RENDERING_VERTEX_ARRAY_H