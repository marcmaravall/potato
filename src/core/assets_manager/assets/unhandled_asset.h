#pragma once

#include <assets_manager/asset.h>

#include <memory>
#include <nlohmann/json.hpp>
#include <string>

namespace PotatoEngine::Core {

class UnhandledAsset : public Asset {
public:
    UnhandledAsset(const std::string& path) {}
    ~UnhandledAsset() override = default;

    nlohmann::json Serialize() const override;
    void Deserialize(const nlohmann::json& j) override;
};

}  // namespace PotatoEngine::Core
