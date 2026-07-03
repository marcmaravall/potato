#pragma once

#include <string>
#include <ecs/component.h>
#include <scripting/scripting_module.h>

namespace PotatoEngine::Core::ECS::Components {
	class LuaScript : public Component {
	public:
		std::string Source;

	public:
		LuaScript() : Component("Lua Script") {}
		~LuaScript() = default;

		void nothing() override {}
	};
}
