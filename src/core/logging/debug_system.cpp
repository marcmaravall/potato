#include "debug_system.h"

using namespace PotatoEngine::Logging;

DebugSystem::DebugSystem() {

}

DebugSystem::~DebugSystem() {

}


void DebugSystem::Log(const DebugSystem::Message& message) {
	m_messages.push_back(message);
}
