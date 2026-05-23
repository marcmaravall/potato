#include "win32.h"

using namespace PotatoEngine::Platform;

bool Win32_API::SetConsoleVisibility(const bool val) {
	HWND hwnd = GetConsoleWindow();
	
	if (!hwnd)
		return true;

	ShowWindow(hwnd, val ? SW_SHOW : SW_HIDE);
	return true;
}
