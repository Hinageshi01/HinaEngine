#pragma once

namespace Hina
{

class Path
{
public:
	Path() = delete;
	Path(const Path &) = delete;
	Path &operator=(const Path &) = delete;
	Path(Path &&) = delete;
	Path &operator=(Path &&) = delete;

	static const std::string FromRoot(const char *str = "");
	static const std::string FromAsset(const char *str = "");

private:
	static std::filesystem::path m_rootPath;
};

} // namespace Hina
