#pragma once

#include <functional>

namespace PotatoEngine::Editor {

	class Command {

	public:
		std::function<void()> Execute;
		std::function<void()> Undo;

	public:
		Command() = default;
		Command(auto execute, auto undo) : Execute(execute), Undo(undo) {}
		~Command() = default;
	};
}
