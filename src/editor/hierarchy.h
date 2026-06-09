#ifndef POTATO_EDITOR_HIERARCHY_H
#define POTATO_EDITOR_HIERARCHY_H

#include "panel.h"
#include <core/engine_context.h>

#include <core/components/camera.h>
#include <core/components/sprite_renderer.h>
#include <core/systems/sprite_renderer.h>

#include <stack>

namespace PotatoEngine::Editor {

	class HierarchyPanel : public EditorPanel {
	public:
		HierarchyPanel(Core::EngineContext& ctx) : EditorPanel("Hierarchy", ctx) {
			/*
			m_engineContext.Entities.push_back(Core::ECS::Entity("Paco"));
			m_engineContext.Entities[0].Add(new Core::Components::SpriteRendererData());
			m_engineContext.Entities[0].Add(new Core::Systems::SpriteRendererSystem(ctx));

			m_engineContext.Entities[0].Children.push_back(Core::ECS::Entity("Hijo de Paco"));

			m_engineContext.Entities.push_back(Core::ECS::Entity("Puta"));
			m_engineContext.Entities[1].Children.push_back(Core::ECS::Entity("te la creiste we xd"));*/
		}

	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_EDITOR_HIERARCHY_H