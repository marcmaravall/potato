#ifndef POTATO_INSPECTOR_H
#define POTATO_INSPECTOR_H

#include <memory>

#include "panel.h"
#include <core/engine_context.h>

#include <format>
#include <typeindex>
#include <functional>
#include <unordered_map>
#include <string>

#include <ecs/components/transform.h>
#include <ecs/components/name.h>
#include <ecs/components/parent.h>
#include <ecs/components/children.h>
#include <ecs/components/sprite_renderer.h>
#include <ecs/components/camera.h>

namespace PotatoEngine::Editor {
	class ComponentInspectorRegistry {
	private:
		std::vector<std::string> m_componentNames;
		std::unordered_map<std::type_index, std::function<void(void*)>> m_renderers;

	public:
		template<typename ComponentType>
		void Add(std::function<void(ComponentType&)> inspectorFunction) {
			m_renderers[typeid(ComponentType)] = [inspectorFunction](void* component) {
				inspectorFunction(*static_cast<ComponentType*>(component));
			};
			m_componentNames.push_back(typeid(ComponentType).name());
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

		// TODO: transform Itanium C++ ABI to something like the msvc implementation
		const std::vector<std::string>& GetComponentNames() const { return m_componentNames; }

		ComponentInspectorRegistry() {
			m_renderers.reserve(10);
		}

		~ComponentInspectorRegistry() = default;
	};

	class Inspector : public EditorPanel {
	private:

	public:
		ComponentInspectorRegistry Registry;

		Inspector(Core::EngineContext& ctx, EditorContext& ectx);
	
	protected:
		void OnBegin() override;
		void OnRender() override;
		void OnEnd() override;
	};
}

#endif // POTATO_INSPECTOR_H