#include "debug_system.h"

using namespace PotatoEngine::Core::Logging;

DebugSystem::DebugSystem() {

}

DebugSystem::~DebugSystem() {

}


void DebugSystem::Log(const DebugSystem::Message& message) {
	m_messages.push_back(message);
}

void DebugSystem::PopLast() {
	m_messages.pop_back();
}

void DebugSystem::Clear() {
	m_messages.clear();
}
