#pragma once

#include <core/assets_manager/asset.h>

#include <sol/sol.hpp>

#include "editor/editor_context.h"
#include "engine_context.h"

namespace PotatoEngine::Editor {

class EditorPlugin {
private:
    sol::environment m_env;
    Core::AssetID m_pluginAssetID = 0;
    bool m_compiled = false;

    EditorContext* m_editorContext;
    Core::EngineContext* m_engineContext;

public:
    EditorPlugin(EditorContext& editorContext,
                 Core::EngineContext& engineContext, Core::AssetID id)
        : m_editorContext(&editorContext),
          m_engineContext(&engineContext),
          m_pluginAssetID(id) {}

    ~EditorPlugin() = default;

    bool Compile(sol::state& lua);
    void Update();

public:
    bool IsCompiled() const { return m_compiled; }
};

}  // namespace PotatoEngine::Editor
