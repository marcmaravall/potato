#include "asset.h"
#include "assets_manager.h"

namespace PotatoEngine::Core {
	Asset::Asset(const std::string& relPath, AssetType type)
		: m_relPath(relPath), m_type(type) {
		
		if (!std::filesystem::exists(relPath)) {
			MEB_LOG_WARNINGF("Asset path does not exist: %s", relPath.c_str());
		}
	}
}