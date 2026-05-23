#include "application.h"

using namespace PotatoEngine::Core;

void Application::Run() {
	OnStart();
	while (m_running)
		OnUpdate();
	OnDestroy();
}
