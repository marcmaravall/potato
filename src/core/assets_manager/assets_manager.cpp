#include "assets_manager.h"

namespace PotatoEngine::Core {
	AssetsManager::AssetsManager() {
		std::filesystem::path currentPath = std::filesystem::current_path();
		
		while (currentPath.has_parent_path() && currentPath.filename() != "potato") {
			currentPath = currentPath.parent_path();
		}

		if (currentPath.filename() == "potato") {
			root = currentPath.string();
		} else {
			assert(0 && "Could not find potato directory in path hierarchy.");
			root = "";
		}
	}

	std::string AssetsManager::Path(const std::string& str) {
		std::string out = str;
#ifdef _WIN32
		for (char& c : out) {
			if (c == '/') c = '\\';
		}
#elif __linux__
		for (char& c : out) {
			if (c == '\\') c = '/';
		}

#endif 
		return out;
	}
}
