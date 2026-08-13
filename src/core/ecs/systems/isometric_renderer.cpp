#include "isometric_renderer.hpp"
#include <engine_context.h>

namespace PotatoEngine::Core::ECS::Systems {

void IsometricRenderer::OnStart() {

}

void IsometricRenderer::OnUpdate() {
	m_context.Registry.ForEachComponentOfType<Components::IsometricGrid>(
		[&](EntityID id, Components::IsometricGrid& grid) {

			for (int i = 0; i < grid.Width; ++i) {
                for (int j = 0; j < grid.Height; ++j) {
                    for (int k = 0; k < grid.Depth; ++k) {
                        float x = (i - j) * 0.5f;
                        float y = (i + j) * 0.25f - k * 0.5f;
                        

                    }
                }
            }

		});
}

void IsometricRenderer::OnDestroy() {

}

}  // namespace PotatoEngine::Core::ECS::Systems