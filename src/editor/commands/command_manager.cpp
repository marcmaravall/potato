#include "command_manager.h"

namespace PotatoEngine::Editor {
	
	void CommandManager::Execute(std::unique_ptr<Command> cmd) {
		cmd->Execute();
		m_undoStack.push(std::move(cmd));
		while (!m_redoStack.empty())
			m_redoStack.pop();
	}

	void CommandManager::Undo() {
		if (m_undoStack.empty())
			return;

		auto cmd = std::move(m_undoStack.top());
		m_undoStack.pop();
		cmd->Undo();

		m_redoStack.push(std::move(cmd));
	}

	void CommandManager::Redo() {
		if (m_redoStack.empty())
			return;

		auto cmd = std::move(m_redoStack.top());
		m_redoStack.pop();
		cmd->Execute();

		m_undoStack.push(std::move(cmd));
	}
}
