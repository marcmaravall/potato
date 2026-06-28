#ifndef POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H
#define POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H

#include <engine_context.h>
#include <ecs/system.h>
#include <ecs/components/sprite_renderer.h>

#include <rendering/vertex_array.h>
#include <rendering/texture2d.h>
#include <rendering/shader_program.h>

#include <memory>

namespace PotatoEngine::Core::ECS::Systems {
	class SpriteRendererSystem : public ECS::System {
	private:
		std::unique_ptr<Core::Rendering::VertexArray> m_vao;
		std::unique_ptr<Core::Rendering::VertexBuffer> m_vbo;
		std::unique_ptr<Core::Rendering::ShaderProgram> m_shaderProgram;
	
	public:
		SpriteRendererSystem(EngineContext& ctx) : ECS::System(ctx) {}
		~SpriteRendererSystem() = default;
	
	protected:
		void OnStart() override;
		void OnUpdate() override;
		void OnDestroy() override;
	};
}

#endif // POTATO_SYSTEMS_SPRITE_RENDERER_SYSTEM_H