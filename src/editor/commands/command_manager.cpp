#include "command_manager.h"

namespace PotatoEngine::Editor {
	
	void CommandManager::Execute(Command cmd) {
		cmd.Execute();
		m_undoStack.push(cmd);
		while (!m_redoStack.empty())
			m_redoStack.pop();
	}

	void CommandManager::Undo() {
		if (m_undoStack.empty())
			return;

		auto cmd = m_undoStack.top();
		m_undoStack.pop();
		cmd.Undo();

		m_redoStack.push(cmd);
	}

	void CommandManager::Redo() {
		if (m_redoStack.empty())
			return;

		auto cmd = m_redoStack.top();
		m_redoStack.pop();
		cmd.Execute();

		m_undoStack.push(cmd);
	}
}
