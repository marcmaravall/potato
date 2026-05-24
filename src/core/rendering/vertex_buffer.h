#ifndef POTATO_VERTEX_BUFFER_H
#define POTATO_VERTEX_BUFFER_H

#include <ref_scope.h>
#include <iostream>
#include "buffer_layout.h"

namespace PotatoEngine::Core::Rendering {
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(const void* data, uint32_t size) = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        static Ref<VertexBuffer> Create(uint32_t size);
        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };
}

#endif // POTATO_VERTEX_BUFFER_H