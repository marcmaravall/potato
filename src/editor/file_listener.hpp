#pragma once

#include <mfsw/mfsw.hpp>

namespace PotatoEngine::Core {
class EngineContext;
}

namespace PotatoEngine::Editor {

class FileListener : public mfsw::watch_listener {
private:
    Core::EngineContext& m_engineContext;

public:
    void on_event(const mfsw::event& event);

public:
    FileListener(Core::EngineContext& ctx) : m_engineContext(ctx) {}
    ~FileListener() = default;
};

}  // namespace PotatoEngine::Editor
