#pragma once

#include <meb.h>
#include <core/engine_context.h>

#include <istream>
#include <fstream>

namespace PotatoEngine::Editor {

class Serializer {
private:

public:
    static void LoadFromFile(Core::EngineContext& ctx, const std::string& path);
    static void SaveToFile(const Core::EngineContext& ctx, const std::string& path);
};

} // namespace PotatoEngine::Editor
