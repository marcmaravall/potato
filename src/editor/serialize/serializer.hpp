#pragma once

#include <core/engine_context.h>
#include <meb.h>

#include <fstream>
#include <istream>

namespace PotatoEngine::Editor {

class Serializer {
private:
public:
    static void LoadFromFile(Core::EngineContext& ctx, const std::string& path);
    static void SaveToFile(const Core::EngineContext& ctx,
                           const std::string& path);
};

}  // namespace PotatoEngine::Editor
