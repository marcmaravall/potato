#include "file_listener.hpp"

#include "assets_manager/asset.h"

namespace PotatoEngine::Editor {

using namespace Core;

// TODO: implement
void FileListener::on_event(const mfsw::event& event) {
    AssetManager& assetManager = m_engineContext._AssetManager;

    MEB_LOG_INFOF("Event received with type %d", (int)event.type);
    MEB_LOG_INFOF("Directory: %s    Filename: %s",
                  event.directory.string().c_str(),
                  event.filename.string().c_str());
    const std::filesystem::path fullPath = event.directory / event.filename;
    if (fullPath.extension() == AssetManager::kMetaExtension) {
        MEB_LOG_INFOF("Skipped because extension was %s",
                      AssetManager::kMetaExtension);
        return;
    }
    const std::filesystem::path metaPath = fullPath.string() + ".meta";
    if (event.type == mfsw::action::MODIFY) {
        if (event.filename.extension() == ".lua") {
            AssetID id = assetManager.GetAssetByPath(fullPath);
            if (!id) return;
            LuaScriptAsset* asset =
                dynamic_cast<LuaScriptAsset*>(assetManager.TryGetAsset(id));
            if (!asset) return;
            // TODO: compile
        }
    }

    if (event.type == mfsw::action::ADD) {
        AssetType type = assetManager.GetAssetType(fullPath);
        AssetID id = assetManager.GenerateRandomAssetID();
        std::unique_ptr<Asset> asset =
            assetManager.CreateAssetInstance(type, fullPath);
        assetManager.WriteMetaFile(metaPath, id, *asset);
        assetManager.UnsafeEmplace(id, std::move(asset));
        MEB_LOG_INFO("Create new asset");
    }
}

}  // namespace PotatoEngine::Editor
