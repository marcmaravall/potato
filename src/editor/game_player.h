#ifndef POTATO_EDITOR_GAME_PLAYER_H
#define POTATO_EDITOR_GAME_PLAYER_H

#include <core/engine_context.h>
#include <core/application.h>
#include <core/executable.h>

#include "panel.h"

namespace PotatoEngine::Editor {
	class GamePlayer : public EditorPanel {
	private:
		Core::Application* m_application;
	public:
		GamePlayer(Core::EngineContext& ctx) : EditorPanel("Game Player", ctx) {
			m_application = new Core::Executable(ctx);
		}

		~GamePlayer() = default;
	public:

		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
};

#endif // POTATO_EDITOR_GAME_PLAYER_H