#include "game_player.h"

namespace PotatoEngine::Editor {

	void GamePlayer::OnBegin() {
		
	}
	
	void GamePlayer::OnRender() {
		if (ImGui::Button("Play") && !m_engineContext.IsRunning) {
			m_engineContext.IsRunning = true;
			m_engineContext.Debug.Log("Game started");

			m_application->OnStart();
		}

		if (m_engineContext.IsRunning) {
			m_application->OnUpdate();
			m_engineContext.SetDeltaTime(1.0 / ImGui::GetIO().Framerate);
		}

		ImGui::SameLine();
		if (ImGui::Button("Next Frame")) {
			
		}
		ImGui::SameLine();
		
		if (ImGui::Button("Stop") && m_engineContext.IsRunning) {
			m_engineContext.IsRunning = false;
			m_engineContext.Debug.Log("Game finished");
		}

		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	}
	
	void GamePlayer::OnEnd() {
		
	}
}
