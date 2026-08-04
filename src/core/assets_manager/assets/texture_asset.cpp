#include "texture_asset.h"

namespace PotatoEngine::Core {

	TextureAsset::TextureAsset(const std::string& path) : Asset(path, AssetType::TEXTURE) {
		Load();
	}

	bool TextureAsset::Load() {
		try {
			m_texture = Rendering::Texture2D::Create(m_absPath.string(), m_settings);

			return true;
		}
		catch (const std::exception& ex) {
			MEB_LOG_ERRORF("Cannot load texture '%s': %s", m_absPath.string().c_str(), ex.what());
			return false;
		}
	}

	nlohmann::json TextureAsset::Serialize() const { 
		return m_settings;
	}

	void TextureAsset::Deserialize(const nlohmann::json& j) {
		m_settings = j.get<Rendering::Texture2D_Settings>();
		Load();
	}

} // namespace PotatoEngine::Core
