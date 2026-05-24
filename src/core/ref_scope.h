#ifndef POTATO_REF_SCOPE_H
#define POTATO_REF_SCOPE_H

#include <memory>

namespace PotatoEngine::Core {
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename... Args>
    Ref<T> createRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    Scope<T> createScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}

#endif // POTATO_REF_SCOPE_H