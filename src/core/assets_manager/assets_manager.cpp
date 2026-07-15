#include "assets_manager.h"

#include "assets/lua_script_asset.h"
#include "assets/texture_asset.h"

namespace PotatoEngine::Core {
	Asset& AssetManager::GetAsset(AssetID id) {
		if (m_map.contains(id)) {
			return *m_map[id];
		} else {
			throw std::runtime_error("Asset with ID " + std::to_string(id) + " not found.");
		}
	}

	Asset* AssetManager::TryGetAsset(AssetID id) {
		if (m_map.contains(id)) {
			return m_map[id].get();
		} else {
			return nullptr;
		}
	}

	AssetID AssetManager::CreateAsset(std::unique_ptr<Asset> asset) {
		AssetID id = m_nextID++;

		m_map.emplace(id, std::move(asset));

		return id;
	}

	AssetManager::AssetManager() {
		std::filesystem::path currentPath = std::filesystem::current_path();
		
		while (currentPath.has_parent_path() && currentPath.filename() != "potato") {
			currentPath = currentPath.parent_path();
		}

		if (currentPath.filename() == "potato") {
			m_root = currentPath.string();
		} else {
			assert(0 && "Could not find potato directory in path hierarchy.");
			m_root = "";
		}
	}

	// TODO: complete:
	AssetType AssetManager::GetAssetType(const std::filesystem::path& path) {
		const auto& ext = path.extension().string();

		if (ext == ".lua")
			return AssetType::LUA_SCRIPT;

		if (ext == ".png" || ext == ".jpg" || ext == ".gif")
			return AssetType::TEXTURE;

		if (ext == ".glsl")
			return AssetType::SHADER;

		if (ext == ".obj" || ext == ".fbx")
			return AssetType::MODEL;

		if (ext == ".wav" || ext == ".ogg")
			return AssetType::SOUND;

		return AssetType::OTHER;
	}

	void AssetManager::ScanAssets() {
		m_map.clear();

		MEB_LOG_INFOF("Scanning Assets; Root: %s", m_root.c_str());

		for (auto& entry : std::filesystem::recursive_directory_iterator(Path(m_root + "/assets"))) {
			if (!entry.is_regular_file())
				continue;

			AssetType type = GetAssetType(entry.path());
			std::unique_ptr<Asset> asset;

			// TODO: put this in a separate function
			switch (type)
			{
			case PotatoEngine::Core::AssetType::SHADER:
				break;
			case PotatoEngine::Core::AssetType::TEXTURE:
				asset = std::make_unique<TextureAsset>(entry.path().string());
				break;
			case PotatoEngine::Core::AssetType::MODEL:
				break;
			case PotatoEngine::Core::AssetType::SOUND:
				break;
			case PotatoEngine::Core::AssetType::ANIMATION:
				break;
			case PotatoEngine::Core::AssetType::TEXT:
				break;
			case PotatoEngine::Core::AssetType::LUA_SCRIPT:
				asset = std::make_unique<LuaScriptAsset>(entry.path().string());
				break;
			case PotatoEngine::Core::AssetType::OTHER:
				break;
			default:
				break;
			}

			AssetID id = CreateAsset(std::move(asset));

			MEB_LOG_INFOF("Create asset '%s' with id %d", entry.path().generic_string().c_str(), id);
		}
	}

	const std::vector<AssetID> AssetManager::GetAssets(AssetType type) {
		std::vector<AssetID> res{};
		for (auto& [id, assetPtr] : m_map) {
			if (assetPtr == nullptr) {
				continue;
			}
			if (assetPtr->GetType() == type) {
				res.push_back(id);
			}
		}
		return res;
	}

	std::string AssetManager::Path(const std::string& str) {
		std::string out = str;
#ifdef _WIN32
		for (char& c : out) {
			if (c == '/') c = '\\';
		}
#elif __linux__
		for (char& c : out) {
			if (c == '\\') c = '/';
		}

#endif 
		return out;
	}
}
