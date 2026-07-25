#pragma once

#include <memory>
#include <stack>

#include "command.h"

namespace PotatoEngine::Editor {

class CommandManager final {
private:
    std::stack<Command> m_undoStack;
    std::stack<Command> m_redoStack;

public:
    void Execute(Command cmd);
    void Undo();
    void Redo();

public:
    CommandManager() = default;
    ~CommandManager() = default;
};
}  // namespace PotatoEngine::Editor
