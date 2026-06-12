#ifndef POTATO_WIN32_H
#define POTATO_WIN32_H

#include "platform/api.h"

namespace PotatoEngine::Platform {
	class Linux_API : public PlatformAPI {
	public:
		Linux_API() { }
		~Linux_API() {}

	public:
		bool SetConsoleVisibility(const bool val) override;
	};
};

#endif // POTATO_WIN32_H