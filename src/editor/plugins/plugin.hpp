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

private:
    void Call(const std::string_view name);

public:
    EditorPlugin(EditorContext& editorContext,
                 Core::EngineContext& engineContext, Core::AssetID id)
        : m_editorContext(&editorContext),
          m_engineContext(&engineContext),
          m_pluginAssetID(id) {}

    ~EditorPlugin() = default;

    bool Compile(sol::state& lua);
    void OnLoad();
    void Update();

public:
    static constexpr const char* kUpdateFunctionName = "_update";
    constexpr static const char* kOnLoadFunctionName = "_onLoad";

public:
    bool IsCompiled() const { return m_compiled; }
};

}  // namespace PotatoEngine::Editor
