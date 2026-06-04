#include "editor_context.h"

using namespace PotatoEngine::Editor;
using namespace PotatoEngine::Core::Logging;

// EditorContext* EditorContext::s_Instance = nullptr;

EditorContext::EditorContext() {
	DebugSystem = Core::Logging::DebugSystem();
	AssetsManager = Core::AssetsManager();
}

EditorContext::~EditorContext() {

}
