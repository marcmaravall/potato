#include "assets_manager.h"

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
