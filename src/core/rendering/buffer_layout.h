#ifndef POTATO_BUFFER_LAYOUT_H
#define POTATO_BUFFER_LAYOUT_H

#include <iostream>
#include <vector>
#include <initializer_list>

namespace PotatoEngine::Core::Rendering {

    enum class ShaderDataType {
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat3, Mat4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float: return 4;
        case ShaderDataType::Float2: return 8;
        case ShaderDataType::Float3: return 12;
        case ShaderDataType::Float4: return 16;
        case ShaderDataType::Int: return 4;
        case ShaderDataType::Int2: return 8;
        case ShaderDataType::Int3: return 12;
        case ShaderDataType::Int4: return 16;
        case ShaderDataType::Mat3: return 48;
        case ShaderDataType::Mat4: return 64;
        case ShaderDataType::Bool: return 1;
        }
    }

    struct BufferElement {
    public:
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement(ShaderDataType t, const std::string& n, bool norm = false)
            : Name(n), Type(t), Size(ShaderDataTypeSize(t)), Offset(0), Normalized(norm) {
        }

        uint32_t GetComponentCount() const { return ShaderDataTypeSize(Type) / 4; }
    };

    class BufferLayout {

    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;

    public:
        BufferLayout() = default;

        BufferLayout(std::initializer_list<BufferElement> elements)
            : m_elements(elements)
        {
            uint32_t offset = 0;
            m_stride = 0;
            for (auto& e : m_elements) {
                e.Offset = offset;
                offset += e.Size;
                m_stride += e.Size;
            }
        }

        uint32_t GetStride() const { return m_stride; }
        const std::vector<BufferElement>& GetElements() const { return m_elements; }

        auto Begin() { return m_elements.begin(); }
        auto End() { return m_elements.end(); }
    };
}

#endif // POTATO_BUFFER_LAYOUT_H