#include "debug.h"

namespace PotatoEngine::Core::Logging {
	Debug::Debug() {
		
	}
	
	Debug::~Debug() {
	
	}
	
	void Debug::Log(const Debug::Message& message) {
		m_messages.push_back(message);
	}
	
	void Debug::PopLast() {
		m_messages.pop_back();
	}
	
	void Debug::Clear() {
		m_messages.clear();
	}
}