#include "texture_asset.h"

namespace PotatoEngine::Core {

	TextureAsset::TextureAsset(const std::string& path) : Asset(path, AssetType::TEXTURE) {
		Load();
	}

	bool TextureAsset::Load() {
		try {
			m_texture = Rendering::Texture2D::Create(m_absPath.string());

			return true;
		}
		catch (const std::exception& ex) {
			MEB_LOG_ERRORF("%s", ex.what());
			return false;
		}
	}
}
