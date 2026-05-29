#ifndef POTATO_TEXTURE_H
#define POTATO_TEXTURE_H

#include <string>
#include <cstdint>

#include <meb.h>
#include <ref_scope.h>

namespace PotatoEngine::Core::Rendering {
	class Texture {
	public:
		virtual ~Texture() = default;

	public:
		Texture() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual int GetWidth()  const = 0;
		virtual int GetHeight() const = 0;
		virtual int GetChannels() const = 0;

	public:
		static Ref<Texture> Create(uint32_t width, uint32_t height);
		static Ref<Texture> Create(const std::string& path);
	};
};

#endif // POTATO_TEXTURE_H