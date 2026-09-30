#include "editor_api.hpp"

#include <core/engine_context.h>

#include <editor/plugins/plugin.hpp>
#include <string>

namespace PotatoEngine::Editor::Scripting {

void InitEditor(sol::state& state) {
    // TODO: init api
    sol::table table = state.create_named_table("EditorAPI");
    table.new_usertype<PluginMeta>(
        "PluginMeta",
        sol::constructors<PluginMeta(const std::string&, const std::string&,
                                     const std::string&)>(),
        "Name", &PluginMeta::Name, "Description", &PluginMeta::Description,
        "Version", &PluginMeta::Version);
}

}  // namespace PotatoEngine::Editor::Scripting
