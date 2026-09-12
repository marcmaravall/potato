#include "file_listener.hpp"

#include "engine_context.h"

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
        MEB_LOG_INFOF("Delete asset with path %s", metaPath.c_str());
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

}  // namespace PotatoEngine::Editor
