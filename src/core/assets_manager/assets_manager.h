#pragma once

#include <iostream>
#include <string>
#include <assert.h>
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <vector>

#include <limits>
#include <random>

#include <nlohmann/json.hpp>

#include "asset.h"

namespace PotatoEngine::Core {
	class AssetManager {
	private:
		std::string m_root = "";
		std::unordered_map<AssetID, std::unique_ptr<Asset>> m_map;

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
		std::unique_ptr<Asset> CreateAssetInstance(AssetType type, const std::filesystem::path& path);
		AssetID GenerateRandomAssetID();
		AssetID GetOrCreateAssetID(const std::filesystem::path& assetPath);

	public:
		void WriteMetaFile(const std::filesystem::path& metaPath, AssetID id, const Asset& asset);
		void LoadMetaFile(const std::filesystem::path& metaPath, AssetID id, Asset& asset);

	public:
		// TODO: optimize to save result so then will be O(1) (returning reference)
		const std::vector<AssetID> GetAssets(AssetType type);
	};

} // namespace PotatoEngine::Core