#pragma once

#include <assets_manager/asset.h>

#include <nlohmann/json.hpp>
#include <string>

namespace PotatoEngine::Core {
class JSON_Asset final : public Asset {
public:
    nlohmann::ordered_json Value;

public:
    void Save();

public:
    JSON_Asset(const std::string& path);
    ~JSON_Asset() override = default;
};

}  // namespace PotatoEngine::Core
