#ifndef POTATO_WIN32_H
#define POTATO_WIN32_H

#ifndef WIN32
#error "Current backend is not supported on this platform!"
#else
#include <Windows.h>
#include <winapifamily.h>
#include <winuser.h>
#endif

#include "platform/api.h"

namespace PotatoEngine::Platform {
	class Win32_API : public PlatformAPI {
	public:
		Win32_API() {}
		~Win32_API() {}

	public:
		bool SetConsoleVisibility(const bool val) override;
	};
};

#endif // POTATO_WIN32_H