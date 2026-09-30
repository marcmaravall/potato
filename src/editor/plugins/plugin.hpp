#pragma once

#include <core/assets_manager/asset.h>

#include <sol/sol.hpp>

#include "editor/editor_context.h"
#include "engine_context.h"

namespace PotatoEngine::Editor {

// This is returned from _getMeta
struct PluginMeta {
    std::string Name = "[NO PLUGIN]";
    std::string Description = "Invalid plugin";
    std::string Version = "1.0.0";

    PluginMeta() = default;
    ~PluginMeta() = default;

    PluginMeta(const std::string& name, const std::string& desc,
               const std::string& vers)
        : Name(name), Description(desc), Version(vers) {}
};

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
    PluginMeta GetMeta();

public:
    constexpr static const char *kUpdateFunctionName = "_update",
                                *kOnLoadFunctionName = "_onLoad",
                                *kGetMetaFunctionName = "_getMeta",
                                *kOnExitFunctionName = "_onExit";

public:
    bool IsCompiled() const { return m_compiled; }
};

}  // namespace PotatoEngine::Editor
