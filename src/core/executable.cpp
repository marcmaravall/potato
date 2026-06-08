#include "executable.h"

namespace PotatoEngine::Core {

	// TODO: implement OnStart and OnDestroy if needed
	void Executable::OnStart() {}

	void Executable::OnUpdate() {
		std::stack<ECS::Entity*> entityStack;

		while (!entityStack.empty()) {
			ECS::Entity* entity = entityStack.top();
			entityStack.pop();

			for (auto system : entity->Systems) {
				system->OnUpdate();
			}
			for (auto& child : entity->Children) {
				entityStack.push(&child);
			}
		}
	}
	
	void Executable::OnDestroy() {} 
}
