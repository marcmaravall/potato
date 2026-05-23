// API for current platform that is managed by the engine

#ifndef POTATO_PLATFORM_API_H
#define POTATO_PLATFORM_API_H

namespace PotatoEngine::Platform {
	class PlatformAPI {
	public:
		PlatformAPI() = default;
		virtual ~PlatformAPI() = default;

	public:
		// Returns true if it's implemented in the current platform
		virtual bool SetConsoleVisibility(const bool val) { return false; }
	};
}

#endif // POTATO_PLATFORM_API_H