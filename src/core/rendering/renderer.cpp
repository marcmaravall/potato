#include "renderer.h"

namespace PotatoEngine::Core::Rendering {
	
	void Renderer::RenderScene() {
		std::queue<ECS::Entity> entityQueue;
		entityQueue.push(m_engineContext.RootEntity);

		// DFS traversal of the hierarchy
		while (!entityQueue.empty()) {
			size_t entityCount = entityQueue.size();

			for (int i = 0; i < entityCount; i++) {
				ECS::Entity& entity = entityQueue.front();
				for (auto& component : entity.Components) {
					if (component.Name == "Sprite Renderer") {
						// TODO: render the sprite
						exit(1);
					}
				}

				entityQueue.pop();

				for (auto& child : entity.Children) {
					entityQueue.push(child);
				}
			}
		}
	}
}
