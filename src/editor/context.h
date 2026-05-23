#ifndef POTATO_EDITOR_CONTEXT_H
#define POTATO_EDITOR_CONTEXT_H

#include <core/logging/debug_system.h>

namespace PotatoEngine::Editor {

	class EditorContext {

	private:

	public:
		EditorContext();
		~EditorContext();

	public:
		Logging::DebugSystem m_debugSystem;
	};
}

#endif // POTATO_EDITOR_CONTEXT_H