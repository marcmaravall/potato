#include "json_asset.hpp"

#include <meb.h>

#include <exception>
#include <fstream>

namespace PotatoEngine::Core {

void JSON_Asset::Save() {
    std::ofstream file(m_absPath);
    if (!file.is_open()) {
        MEB_LOG_ERRORF("JSON_Asset: Cannot save to file %s",
                       m_absPath.string().c_str());
        return;
    }

    file << Value.dump(4);
}

JSON_Asset::JSON_Asset(const std::string& path) : Asset(path, AssetType::JSON) {
    try {
        Value = nlohmann::json::parse(std::ifstream(path));
        MEB_LOG_INFOF(
            "JSON_Asset: Created json object successfully from path %s",
            path.c_str());
    } catch (const nlohmann::json::parse_error& error) {
        MEB_LOG_ERRORF("JSON_Asset: Error parsing json %s", error.what());
    } catch (const std::exception& ex) {
        MEB_LOG_ERRORF("JSON_Asset: %s", ex.what());
    }
}

}  // namespace PotatoEngine::Core
