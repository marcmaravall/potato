#ifndef POTATO_ASSETS_MANAGER_H
#define POTATO_ASSETS_MANAGER_H

#include <iostream>
#include <string>
#include <assert.h>
#include <filesystem>

namespace PotatoEngine::Core {
	class AssetsManager {
	private:
		std::string root = "";

	public:
		AssetsManager();
		~AssetsManager() = default;

		std::string GetRoot() const { return root; }

		static std::string Path(const std::string& str);
	};
}

#endif // POTATO_ASSETS_MANAGER_H