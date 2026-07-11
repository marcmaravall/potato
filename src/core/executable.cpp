#include "executable.h"

namespace PotatoEngine::Core {

	void Executable::OnStart() {
		
		m_context.Registry.Start();
	}

	void Executable::OnUpdate() {
		m_context.Registry.Update();
	}
	
	void Executable::OnDestroy() {
		m_context.Registry.Destroy();
	} 
}
