// TODO: implement

#ifndef POTATO_FILESYSTEM_H
#define POTATO_FILESYSTEM_H

namespace PotatoEngine::Core {
	class Filesystem {
	public:
		static std::string ReadFile(const std::string& filepath);
	};
};

#endif // POTATO_FILESYSTEM_H