#ifndef POTATO_EDITOR_STYLE_H
#define POTATO_EDITOR_STYLE_H

#include <imgui.h>

namespace PotatoEngine::Editor {
	class Theme {
	public:
		static void SetCapMotchaTheme();
		static void SetDarkTheme();
		static void SetLightTheme();
	};
};

#endif // POTATO_EDITOR_STYLE_H