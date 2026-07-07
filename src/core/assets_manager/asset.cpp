#include "asset.h"
#include "assets_manager.h"

namespace PotatoEngine::Core {
	Asset::Asset(const std::string& absPath, AssetType type)
		: m_absPath(absPath), m_type(type) {
		
		if (!std::filesystem::exists(absPath)) {
			MEB_LOG_WARNINGF("Asset path does not exist: %s", absPath.c_str());
		}
	}
}