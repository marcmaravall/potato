#include "engine_context.h"
#include <core/rendering/renderer.h>

namespace PotatoEngine::Core {
	EngineContext::EngineContext()
		: Renderer(*this)
	{
		DebugSystem.Log("Engine context created.");
	}
	
	EngineContext::~EngineContext() {
		DebugSystem.Log("Engine context destroyed.");
	}
}
