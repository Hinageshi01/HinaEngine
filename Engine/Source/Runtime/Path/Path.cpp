#include "hnpch.h"
#include "Path.h"

namespace Hina
{

std::filesystem::path Path::m_rootPath = HN_ENGINE_ROOT_PATH;

const std::string Path::FromRoot(const char *str) {
	return (m_rootPath / str).string();
}

const std::string Path::FromAsset(const char *str) {
	static const std::filesystem::path assetPath = (m_rootPath / "Engine/Source/Asset");
	return (assetPath / str).string();
}

} // namespace Hina
