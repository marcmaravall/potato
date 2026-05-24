#include "context.h"

using namespace PotatoEngine::Editor;
using namespace PotatoEngine::Core::Logging;

EditorContext::EditorContext() {
	m_debugSystem = DebugSystem();
}

EditorContext::~EditorContext() {

}
