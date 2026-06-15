#include "opengl_vertex_array.h"

using namespace PotatoEngine::Core::Rendering;

void OpenGL_VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vb) {
    MEB_ASSERT(!vb->GetLayout().GetElements().empty() && "Vertex buffer has no layout!");

    glBindVertexArray(m_id);
    vb->Bind();

    uint32_t index = 0;
    const std::vector<BufferElement>& layout = vb->GetLayout().GetElements();

    for (const auto& element : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            element.GetComponentCount(),
            GL_FLOAT,
            element.Normalized ? GL_TRUE : GL_FALSE,
            vb->GetLayout().GetStride(), 
            (const void*)(uintptr_t)element.Offset
        );

        index++;
    }

    m_vertexBuffers.push_back(vb);
}
