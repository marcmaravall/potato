#include "file_listener.hpp"

#include "engine_context.h"
#include <string>

namespace PotatoEngine::Editor {

using namespace Core;

static const char* ActionToString(const mfsw::action action) {
    switch (action) {
        case mfsw::action::ADD:
            return "ADD";
        case mfsw::action::REMOVE:
            return "REMOVE";
        case mfsw::action::MODIFY:
            return "MODIFY";
        case mfsw::action::MOVE:
            return "MOVE";
        default:
            return "NONE";
    }
}

void FileListener::on_event(const mfsw::event& event) {
    AssetManager& assetManager = m_engineContext._AssetManager;

    MEB_LOG_INFOF("Event received with type %s", ActionToString(event.type));
    MEB_LOG_INFOF("Directory: %s    Filename: %s",
                  event.directory.string().c_str(),
                  event.filename.string().c_str());
    const std::filesystem::path fullPath = event.directory / event.filename;
    const std::filesystem::path oldFullPath =
        event.old_directory / event.old_filename;
    const std::filesystem::path oldMetaPath =
        oldFullPath.string() + AssetManager::kMetaExtension;

    bool isDir = std::filesystem::is_directory(fullPath) || event.is_directory;
    if (isDir) {
        if (event.type == mfsw::action::REMOVE) {
            OnRemoveFolder(fullPath);
        } else if (event.type == mfsw::action::MOVE) {
            OnMoveFolder(oldFullPath);
        }
        return;
    }

    constexpr const char* NEOVIM_BUFFER_FILE = (const char*)"4913";
    if (event.filename == NEOVIM_BUFFER_FILE) {
        // Ignore neovim buffer
        return;
    }

    if (fullPath.extension() == AssetManager::kMetaExtension) {
        MEB_LOG_INFOF("Skipped because extension was %s",
                      AssetManager::kMetaExtension);
        return;
    }
    const std::filesystem::path metaPath =
        fullPath.string() + AssetManager::kMetaExtension;
    if (event.type == mfsw::action::MODIFY) {
        // Do some shit depending on the asset
    }

    if (event.type == mfsw::action::ADD) {
        try {
            AssetType type = assetManager.GetAssetType(fullPath);
            AssetID id = assetManager.GenerateRandomAssetID();
            std::unique_ptr<Asset> asset =
                assetManager.CreateAssetInstance(type, fullPath);
            assetManager.WriteMetaFile(metaPath, id, *asset);
            assetManager.UnsafeEmplace(id, std::move(asset));
            MEB_LOG_INFO("Create new asset");
        } catch (std::exception& ex) {
            MEB_LOG_ERRORF("%s", ex.what());
        }
    }

    if (event.type == mfsw::action::REMOVE) {
        AssetID id = assetManager.GetAssetByPath(metaPath);
        assetManager.RemoveAsset(id);
        std::filesystem::remove(metaPath);
        MEB_LOG_INFOF("Delete asset with path %s", metaPath.string().c_str());
    }

    if (event.type == mfsw::action::MOVE) {
        AssetID id = assetManager.GetAssetByPath(oldMetaPath);
        if (id) {
            std::filesystem::rename(oldMetaPath, metaPath);
            if (!assetManager.UpdateAssetPath(id, fullPath)) {
                MEB_LOG_ERROR("Cannot update asset path");
            }
            MEB_LOG_INFOF("Moved asset %s -> %s", oldFullPath.string().c_str(),
                          fullPath.string().c_str());
        } else {
            try {
                assetManager.LoadOrCreateAsset(fullPath, metaPath);
            } catch (std::exception& ex) {
                MEB_LOG_ERRORF("%s", ex.what());
            }
        }
    }
}

void FileListener::OnRemoveFolder(const std::filesystem::path& folderPath) {
    AssetManager& assetManager = m_engineContext._AssetManager;
    const auto& assets = assetManager.GetAssets();
    MEB_LOG_INFOF("Removing assets from folder %s",
                  folderPath.string().c_str());
    for (const auto& [id, asset] : assets) {
        const auto& assetPath = asset->GetAbsolutePath();
        std::error_code ec;
        const auto relativePath =
            std::filesystem::relative(assetPath, folderPath, ec);
        MEB_LOG_INFOF("Processing asset %s", assetPath.string().c_str());
        if (ec || relativePath.empty() || relativePath == ".." ||
            relativePath.string().starts_with(
                ".." +
                std::string(1, std::filesystem::path::preferred_separator))) {
            continue;
        }
        assetManager.RemoveAsset(id);
        const auto metaPath = assetPath.string() + AssetManager::kMetaExtension;
        std::filesystem::remove(metaPath, ec);
        MEB_LOG_INFOF("Removed asset with path %s", assetPath.string().c_str());
    }
}

void FileListener::OnMoveFolder(const std::filesystem::path& oldFolderPath) {
    // TODO: implement
}

}  // namespace PotatoEngine::Editor
