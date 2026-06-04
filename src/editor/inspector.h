#ifndef POTATO_INSPECTOR_H
#define POTATO_INSPECTOR_H

#include <memory>

#include "panel.h"

namespace PotatoEngine::Editor {

	class Inspector : public EditorPanel {
	public:
		Inspector(EditorContext& ctx) : EditorPanel("Inspector", ctx) {}
	
	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_INSPECTOR_H