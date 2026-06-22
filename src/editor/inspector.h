#ifndef POTATO_INSPECTOR_H
#define POTATO_INSPECTOR_H

#include <memory>

#include "panel.h"
#include <core/engine_context.h>

#include <typeindex>
#include <functional>
#include <unordered_map>

#include <ecs/components/sprite_renderer.h>
#include <ecs/components/camera.h>

namespace PotatoEngine::Editor {
	class ComponentInspectorRegistry {
	private:
		std::unordered_map<std::type_index, std::function<void(void*)>> m_renderers;

	public:
		template<typename ComponentType>
		void Add(std::function<void(ComponentType&)> inspectorFunction) {
			m_renderers[typeid(ComponentType)] = [inspectorFunction](void* component) {
				inspectorFunction(*static_cast<ComponentType*>(component));
			};
		}

		void Render(void* component, std::type_index type) {
			auto it = m_renderers.find(type);
			if (it != m_renderers.end()) {
				it->second(component);
			}
			else {
				ImGui::TextDisabled("No inspector for: %s", type.name());
			}
		}

		void Render(Core::ECS::Component* c) {
			auto it = m_renderers.find(typeid(*c));
			if (it != m_renderers.end())
				it->second(c);
			else
				ImGui::TextDisabled("No inspector for: %s", typeid(*c).name());
		}

		ComponentInspectorRegistry() {
			m_renderers.reserve(10);
		}

		~ComponentInspectorRegistry() = default;
	};

	class Inspector : public EditorPanel {
	private:

	public:
		ComponentInspectorRegistry Registry;

		Inspector(Core::EngineContext& ctx) : EditorPanel("Inspector", ctx) {
			Registry.Add<Core::Components::SpriteRendererData>([](Core::Components::SpriteRendererData& sr) {
				ImGui::ColorEdit4("Color", &sr.Color[0]);
				ImGui::InputFloat2("Pivot", &sr.Pivot[0]);
				ImGui::Checkbox("Flip X", &sr.FlipX);
				ImGui::Checkbox("Flip Y", &sr.FlipY);
			});

			Registry.Add<Core::Components::CameraData>([](Core::Components::CameraData& c) {
				ImGui::ColorEdit3("Clear Color", &c.ClearColor[0]);
			});
		}
	
	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_INSPECTOR_H