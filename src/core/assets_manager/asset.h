#ifndef POTATO_ASSET_H
#define POTATO_ASSET_H

namespace PotatoEngine::Core {
	enum class AssetType {
		SHADER,
		TEXTURE,
		MODEL,
		SOUND,
		ANIMATION,
		TEXT,
		OTHER
	};
	
	class Asset {
	protected:

	public:
		virtual AssetType AssetType() const = 0;
		virtual ~Asset() = default;
	};
};

#endif // POTATO_ASSET_H