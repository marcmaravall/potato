#include "debug_system.h"

using namespace PotatoEngine::Core::Logging;
DebugSystem* DebugSystem::s_Instance = nullptr;

DebugSystem::DebugSystem() {
	if (s_Instance == nullptr) {
		s_Instance = this;
	}
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
