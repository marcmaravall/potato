#pragma once

#include <assets_manager/asset.h>
#include <serialize/meta.hpp>

namespace PotatoEngine::Core {

static constexpr const char* kSceneExtension = (const char*)".pscene";
class SceneAsset : public Asset {

public:
    SceneAsset(const std::string& path) : Asset(path, AssetType::SCENE) {}
    ~SceneAsset() override = default;
};

}  // namespace PotatoEngine::Core