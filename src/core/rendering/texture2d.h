#ifndef POTATO_TEXTURE_H
#define POTATO_TEXTURE_H

#include <string>
#include <cstdint>

#include <meb.h>
#include <ref_scope.h>

namespace PotatoEngine::Core::Rendering {
	class Texture2D {
	public:
		virtual ~Texture2D() = default;

	public:
		Texture2D() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual int GetWidth()  const = 0;
		virtual int GetHeight() const = 0;
		virtual int GetChannels() const = 0;

	public:
		static Scope<Texture2D> Create(uint32_t width, uint32_t height);
		static Scope<Texture2D> Create(const std::string& path);
	};
};

#endif // POTATO_TEXTURE_H