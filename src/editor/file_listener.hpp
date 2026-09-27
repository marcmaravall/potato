#pragma once

#include <mfsw/mfsw.hpp>
#include <unordered_map>
#include <chrono>
#include <assets_manager/asset.h>
#include <regex>

namespace PotatoEngine::Core {
class EngineContext;
}

namespace PotatoEngine::Editor {

class FileListener : public mfsw::watch_listener {
private:
    Core::EngineContext& m_engineContext;

    constexpr static std::chrono::milliseconds kRemoveDelay =
        std::chrono::milliseconds(50);

    struct PendingRemoval {
        Core::AssetID ID;
        std::chrono::steady_clock::time_point Time;
    };

    std::unordered_map<std::filesystem::path, PendingRemoval> m_pendingRemovals;

private:
    bool IsTempFile(const std::filesystem::path& path);

    void OnRemoveFolder(const std::filesystem::path& path);
    void OnMoveFolder(const std::filesystem::path& path);

public:
    void on_event(const mfsw::event& event);

public:
    FileListener(Core::EngineContext& ctx) : m_engineContext(ctx) {}
    ~FileListener() = default;
};

}  // namespace PotatoEngine::Editor
