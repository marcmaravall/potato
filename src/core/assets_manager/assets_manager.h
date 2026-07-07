#ifndef POTATO_ASSETS_MANAGER_H
#define POTATO_ASSETS_MANAGER_H

#include <iostream>
#include <string>
#include <assert.h>
#include <filesystem>
#include <unordered_map>
#include <memory>

#include "asset.h"

namespace PotatoEngine::Core {
	class AssetManager {
	private:
		std::string m_root = "";
		std::unordered_map<AssetID, std::unique_ptr<Asset>> m_map;
		AssetID m_nextID = 0;

	public:
		AssetManager();
		~AssetManager() = default;

		Asset& GetAsset(AssetID id);
		Asset* TryGetAsset(AssetID id);
		AssetID CreateAsset(std::unique_ptr<Asset> asset);

		const std::string& GetRoot() const { return m_root; }

		static std::string Path(const std::string& str);
	};
}

#endif // POTATO_ASSETS_MANAGER_H