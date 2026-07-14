#ifndef POTATO_ASSETS_MANAGER_H
#define POTATO_ASSETS_MANAGER_H

#include <iostream>
#include <string>
#include <assert.h>
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <vector>

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

		AssetType GetAssetType(const std::filesystem::path& path);

		void ScanAssets();

		const std::string& GetRoot() const { return m_root; }

		static std::string Path(const std::string& str);

	public:
		// TODO: optimize to save result so then will be O(1)
		const std::vector<AssetID> GetAssets(AssetType type);
	};
}

#endif // POTATO_ASSETS_MANAGER_H