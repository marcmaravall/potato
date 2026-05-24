#ifndef POTATO_FRAMEBUFFER_H
#define POTATO_FRAMEBUFFER_H

#include <vector>
#include <iostream>
#include <ref_scope.h>

namespace PotatoEngine::Core::Rendering {

    enum class FramebufferTextureFormat {
        None = 0,
        RGBA8,
        RED_INTEGER,
        DEPTH24STENCIL8,
        Depth = DEPTH24STENCIL8
    };

    class FramebufferTextureSpec {
    public:
        FramebufferTextureFormat Format = FramebufferTextureFormat::None;
    };

    class FramebufferAttachmentSpec {
    public:
        std::vector<FramebufferTextureSpec> Attachments;
    };

    class FramebufferSpec {
    public:
        FramebufferAttachmentSpec Attachments;
        uint32_t Width = 0;
        uint32_t Height = 0;
        uint32_t Samples = 1;
        bool SwapChainTarget = false;
    };

	class Framebuffer {
    public:
        virtual ~Framebuffer() = default;

    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual int  ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;
        virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

        virtual uint32_t GetColorAttachmentID(uint32_t index = 0) const = 0;

        virtual const FramebufferSpec& GetSpec() const = 0;

        static Ref<Framebuffer> Create(const FramebufferSpec& spec);
	};
}

#endif // POTATO_FRAMEBUFFER_H