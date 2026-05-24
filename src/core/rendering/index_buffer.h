#ifndef POTATO_INDEX_BUFFER_H
#define POTATO_INDEX_BUFFER_H

#include <ref_scope.h>

namespace PotatoEngine::Core::Rendering {
	class IndexBuffer {

    public:
        virtual ~IndexBuffer() = default;
    
    public:
        virtual void Bind()   const = 0;
        virtual void Unbind() const = 0;
        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
};

#endif // POTATO_INDEX_BUFFER_H