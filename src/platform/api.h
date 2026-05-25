// API for current platform that is managed by the engine

#ifndef POTATO_PLATFORM_API_H
#define POTATO_PLATFORM_API_H

#include <iostream>

namespace PotatoEngine::Platform {
	class PlatformAPI {
	public:
		PlatformAPI() {
			if (s_Instance == nullptr)
				s_Instance = this;
		}

		virtual ~PlatformAPI() = default;

	public:
		// Returns true if it's implemented in the current platform
		virtual bool SetConsoleVisibility(const bool val) { return false; }

	public:
		static PlatformAPI *s_Instance;
	};
}

#endif // POTATO_PLATFORM_API_H