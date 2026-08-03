#pragma once

#include <string>
#include <cstdint>

#include <meb.h>
#include <ref_scope.h>

#include <nlohmann/json.hpp>

namespace PotatoEngine::Core::Rendering {

enum class TextureFilter {
	POINT,
	BILINEAR,
	TRILINEAR
};

NLOHMANN_JSON_SERIALIZE_ENUM(TextureFilter, {
	{TextureFilter::POINT, "POINT"},
	{TextureFilter::BILINEAR, "BILINEAR"},
	{TextureFilter::TRILINEAR, "TRILINEAR"}
})

enum class TextureWrap {
	REPEAT,
	MIRRORED_REPEAT,
	CLAMP_TO_EDGE,
    CLAMP_TO_BORDER
};

NLOHMANN_JSON_SERIALIZE_ENUM(TextureWrap, {
	{TextureWrap::REPEAT, "REPEAT"},
	{TextureWrap::MIRRORED_REPEAT, "MIRRORED_REPEAT"},
	{TextureWrap::CLAMP_TO_EDGE, "CLAMP_TO_EDGE"},
	{TextureWrap::CLAMP_TO_BORDER, "CLAMP_TO_BORDER"}
})

class Texture2D_Settings {
public:
    TextureFilter Filter = TextureFilter::BILINEAR;
    TextureWrap WrapS = TextureWrap::REPEAT;
    TextureWrap WrapT = TextureWrap::REPEAT;

public:
    Texture2D_Settings() = default;
    ~Texture2D_Settings() = default;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Texture2D_Settings, Filter, WrapS, WrapT)
};

class Texture2D {
	public:
		virtual ~Texture2D() = default;

	public:
		Texture2D() = default;
		virtual void Bind(uint32_t slot) = 0;
		virtual void Unbind() = 0;

		virtual int GetWidth()  const = 0;
		virtual int GetHeight() const = 0;
		virtual int GetChannels() const = 0;

	public:
		static Scope<Texture2D> Create(uint32_t width, uint32_t height);
		static Scope<Texture2D> Create(const std::string& path, const Texture2D_Settings& settings = Texture2D_Settings());
};

}  // namespace PotatoEngine::Core::Rendering
