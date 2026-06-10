#include "executable.h"

namespace PotatoEngine::Core {

	// TODO: implement OnStart and OnDestroy if needed
	void Executable::OnStart() {
		/*std::stack<ECS::Entity*> entityStack;

		for (auto& entity : m_context.Entities) {
			entityStack.push(&entity);
		}

		while (!entityStack.empty()) {
			ECS::Entity* entity = entityStack.top();
			entityStack.pop();

			for (auto* system : entity->Systems) {
				system->OnStart();
			}

			for (auto& child : entity->Children) {
				entityStack.push(&child);
			}
		}*/
	}

	void Executable::OnUpdate() {
		/*std::stack<ECS::Entity*> entityStack;

		for (auto& entity : m_context.Entities) {
			entityStack.push(&entity);
		}

		while (!entityStack.empty()) {
			ECS::Entity* entity = entityStack.top();
			entityStack.pop();

			for (auto* system : entity->Systems) {
				system->OnUpdate();
			}

			for (auto& child : entity->Children) {
				entityStack.push(&child);
			}
		}
		*/
	}
	
	void Executable::OnDestroy() {
		/*std::stack<ECS::Entity*> entityStack;

		for (auto& entity : m_context.Entities) {
			entityStack.push(&entity);
		}

		while (!entityStack.empty()) {
			ECS::Entity* entity = entityStack.top();
			entityStack.pop();

			for (auto* system : entity->Systems) {
				system->OnDestroy();
			}

			for (auto& child : entity->Children) {
				entityStack.push(&child);
			}
		}*/
	} 
}
