#pragma once

#include <memory>
#include <stack>

#include "command.h"

namespace PotatoEngine::Editor {

class CommandManager final {
private:
    std::stack<ICommand*> m_undoStack;
    std::stack<ICommand*> m_redoStack;

public:
    void Execute(ICommand* cmd);
    void Undo();
    void Redo();

public:
    CommandManager() = default;
    ~CommandManager();
};
}  // namespace PotatoEngine::Editor
