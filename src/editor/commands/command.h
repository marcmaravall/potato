#pragma once

#include <functional>

namespace PotatoEngine::Editor {

class ICommand {
public:
    virtual void Execute() = 0;
    virtual void Undo() = 0;

public:
    ICommand() = default;
    virtual ~ICommand() = default;
};

}  // namespace PotatoEngine::Editor
