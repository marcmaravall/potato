#ifndef POTATO_EDITOR_CONTEXT_H
#define POTATO_EDITOR_CONTEXT_H

#include <core/logging/debug.h>

#include <core/ecs/entity_id.h>
#include <core/assets_manager/assets_manager.h>

namespace PotatoEngine::Editor {

	class EditorContext {

	private:


	public:
		EditorContext();
		~EditorContext();

	public:
		Core::ECS::EntityID SelectedEntity;
		bool IsEntitySelected = false;

	public:
		// static EditorContext* s_Instance;
	};
}

#endif // POTATO_EDITOR_CONTEXT_H