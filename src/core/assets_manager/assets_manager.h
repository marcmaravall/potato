#pragma once

#include <assert.h>

#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <mfsw/mfsw.hpp>
#include <nlohmann/json.hpp>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "asset.h"

namespace PotatoEngine::Core {
class AssetManager {
private:
    std::string m_root = "";
    std::unordered_map<AssetID, std::unique_ptr<Asset>> m_map;

public:
    AssetManager();
    ~AssetManager() = default;

    void UnsafeEmplace(AssetID id, std::unique_ptr<Asset> asset);

    void SetRoot(const std::filesystem::path& root);
    Asset& GetAsset(AssetID id);
    Asset* TryGetAsset(AssetID id);

    void ClearAssets();
    void RemoveAsset(AssetID id);

    void LoadOrCreateAsset(const std::filesystem::path& path,
                           const std::filesystem::path& meta);

    AssetID GetAssetByPath(const std::filesystem::path& path);

    AssetID CreateAsset(std::unique_ptr<Asset> asset);
    bool UpdateAssetPath(AssetID id, const std::filesystem::path& path);

    AssetType GetAssetType(const std::filesystem::path& path);

    void ScanAssets();

    const std::string& GetRoot() const { return m_root; }

    static std::string Path(const std::string& str);

public:
    std::unique_ptr<Asset> CreateAssetInstance(
        AssetType type, const std::filesystem::path& path);
    AssetID GenerateRandomAssetID();
    AssetID GetOrCreateAssetID(const std::filesystem::path& assetPath);

public:
    // Checks if a file is used like an asset by the AssetManager in O(N)
    bool IsAssetFile(const std::filesystem::path& path);

public:
    void WriteMetaFile(const std::filesystem::path& metaPath, AssetID id,
                       const Asset& asset);
    void LoadMetaFile(const std::filesystem::path& metaPath, AssetID id,
                      Asset& asset);

public:
    static constexpr const char* kMetaExtension = ".meta";

public:
    // TODO: optimize to save result so then will be O(1) (returning
    // reference)
    const std::vector<AssetID> GetAssets(AssetType type);
};

}  // namespace PotatoEngine::Core
