#include "assets_manager.h"

#include <filesystem>
#include <fstream>
#include <limits>
#include <random>

#include "assets/lua_script_asset.h"
#include "assets/texture_asset.h"

namespace PotatoEngine::Core {

namespace {

constexpr const char* kMetaIdKey = "id";
constexpr const char* kMetaDataKey = "data";
}  // namespace

Asset& AssetManager::GetAsset(AssetID id) {
    if (m_map.contains(id)) {
        return *m_map[id];
    } else {
        throw std::runtime_error("Asset with ID " + std::to_string(id) +
                                 " not found.");
    }
}

Asset* AssetManager::TryGetAsset(AssetID id) {
    if (m_map.contains(id)) {
        return m_map[id].get();
    } else {
        return nullptr;
    }
}

AssetID AssetManager::GetAssetByPath(const std::filesystem::path& path) {
    if (std::filesystem::exists(path)) return 0;

    if (strcmp(path.extension().c_str(), kMetaExtension) == 0) {
        std::ifstream f(path);
        nlohmann::json metaJson;
        f >> metaJson;

        AssetID id = metaJson.at(kMetaIdKey);
        return id;
    }
    return 0;
}

AssetID AssetManager::CreateAsset(std::unique_ptr<Asset> asset) {
    AssetID id = GenerateRandomAssetID();

    m_map.emplace(id, std::move(asset));

    return id;
}

// TODO: don't do this
AssetManager::AssetManager() {
    std::filesystem::path currentPath = std::filesystem::current_path();
#define MAX_ITERATIONS 100
    int iterations = 0;
    while (currentPath.has_parent_path() &&
           currentPath.filename().string().find("potato") ==
               std::string::npos &&
           iterations < MAX_ITERATIONS) {
        currentPath = currentPath.parent_path();
        iterations++;
    }

    if (iterations == MAX_ITERATIONS) {
        MEB_ASSERT(0 && "Could not find potato directory in path hierarchy.");
        m_root = "";
        return;
    }

    if (currentPath.filename().string().find("potato") != std::string::npos) {
        m_root = currentPath.string();
    } else {
        MEB_ASSERT(0 && "Could not find potato directory in path hierarchy.");
        m_root = "";
    }
}

// TODO: complete:
AssetType AssetManager::GetAssetType(const std::filesystem::path& path) {
    const auto& ext = path.extension().string();

    if (ext == ".lua") return AssetType::LUA_SCRIPT;

    if (ext == ".png" || ext == ".jpg" || ext == ".gif")
        return AssetType::TEXTURE;

    if (ext == ".glsl") return AssetType::SHADER;

    if (ext == ".obj" || ext == ".fbx") return AssetType::MODEL;

    if (ext == ".wav" || ext == ".ogg") return AssetType::SOUND;

    return AssetType::OTHER;
}

std::unique_ptr<Asset> AssetManager::CreateAssetInstance(
    AssetType type, const std::filesystem::path& path) {
    switch (type) {
        case AssetType::SHADER:
            return nullptr;
        case AssetType::TEXTURE:
            return std::make_unique<TextureAsset>(path.string());
        case AssetType::MODEL:
            return nullptr;
        case AssetType::SOUND:
            return nullptr;
        case AssetType::ANIMATION:
            return nullptr;
        case AssetType::TEXT:
            return nullptr;
        case AssetType::LUA_SCRIPT:
            return std::make_unique<LuaScriptAsset>(path.string());
        case AssetType::OTHER:
        default:
            return nullptr;
    }
}

AssetID AssetManager::GenerateRandomAssetID() {
    static std::mt19937_64 rng{std::random_device{}()};
    static std::uniform_int_distribution<AssetID> dist(1, UINT64_MAX);

    AssetID id;
    do {
        id = dist(rng);
    } while (m_map.contains(id) || id == 0);

    return id;
}

void AssetManager::WriteMetaFile(const std::filesystem::path& metaPath,
                                 AssetID id, const Asset& asset) {
    nlohmann::json metaJson;
    metaJson[kMetaIdKey] = id;
    metaJson[kMetaDataKey] = asset.Serialize();

    std::ofstream metaFile(metaPath);
    if (!metaFile.is_open()) {
        MEB_LOG_WARNINGF("Could not write meta file '%s'.",
                         metaPath.string().c_str());
        return;
    }
    metaFile << metaJson.dump(4);
}

void AssetManager::LoadMetaFile(const std::filesystem::path& metaPath,
                                AssetID id, Asset& asset) {
    std::ifstream metaFile(metaPath);
    nlohmann::json metaJson;
    metaFile >> metaJson;

    try {
        asset.Deserialize(metaJson.at(kMetaDataKey));
    } catch (const std::exception& e) {
        MEB_LOG_WARNINGF("Failed to deserialize meta file '%s' (%s)",
                         metaPath.string().c_str(), e.what());
    }
}

AssetID AssetManager::GetOrCreateAssetID(
    const std::filesystem::path& assetPath) {
    std::filesystem::path metaPath = assetPath;
    metaPath += kMetaExtension;

    if (std::filesystem::exists(metaPath)) {
        std::ifstream metaFile(metaPath);
        try {
            nlohmann::json metaJson;
            metaFile >> metaJson;

            if (metaJson.contains(kMetaIdKey)) {
                AssetID id = metaJson.at(kMetaIdKey).get<AssetID>();

                if (id != 0 && !m_map.contains(id)) return id;

                MEB_LOG_WARNINGF(
                    "Meta file '%s' has an invalid or duplicate id (%llu); "
                    "regenerating.",
                    metaPath.string().c_str(),
                    static_cast<unsigned long long>(id));
            }
        } catch (const std::exception& e) {
            MEB_LOG_WARNINGF(
                "Failed to parse meta file '%s' (%s); regenerating.",
                metaPath.string().c_str(), e.what());
        }
    }

    AssetID id = GenerateRandomAssetID();
    return id;
}

void AssetManager::ScanAssets() {
    m_map.clear();

    MEB_LOG_INFOF("Scanning Assets; Root: %s", m_root.c_str());

    for (auto& entry : std::filesystem::recursive_directory_iterator(
             Path(m_root + "/assets"))) {
        if (!entry.is_regular_file()) continue;

        if (entry.path().extension() == kMetaExtension) continue;

        AssetType type = GetAssetType(entry.path());
        std::unique_ptr<Asset> asset = CreateAssetInstance(type, entry.path());

        if (asset == nullptr) {
            MEB_LOG_INFOF("Skipping unsupported asset type for file: %s",
                          entry.path().string().c_str());
            continue;
        }

        const auto& metaPath = entry.path().string() + kMetaExtension;

        bool existsMeta = std::filesystem::exists(metaPath);

        AssetID id = GetOrCreateAssetID(entry.path());

        if (!existsMeta) {
            WriteMetaFile(metaPath, id, *asset);
        }

        LoadMetaFile(metaPath, id, *asset);

        MEB_LOG_INFOF("Create asset '%s', Extension: %s, ID %llu",
                      entry.path().generic_string().c_str(),
                      entry.path().extension().c_str(),
                      static_cast<unsigned long long>(id));

        m_map.emplace(id, std::move(asset));
    }
}

bool AssetManager::IsAssetFile(const std::filesystem::path& path) {
    return strcmp(path.extension().c_str(), kMetaExtension) != 0;
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

}  // namespace PotatoEngine::Core
