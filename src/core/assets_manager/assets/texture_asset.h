#pragma once

#include <memory>
#include <string>
#include <assets_manager/asset.h>
#include <meb.h>
#include <rendering/texture2d.h>

namespace PotatoEngine::Core {
	class TextureAsset : public Asset {
	private:
		std::unique_ptr<Rendering::Texture2D> m_texture;

	public:
		TextureAsset(const std::string& path);
		~TextureAsset() override = default;

		Rendering::Texture2D* GetTexture() const { return m_texture.get(); }

		bool Load();
	};
};
