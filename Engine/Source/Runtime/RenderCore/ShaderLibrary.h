#pragma once

#include "RenderCore/Shader.h"

namespace Hina
{

class ShaderLibrary
{
public:
	ShaderLibrary() = default;
	ShaderLibrary(const ShaderLibrary &) = default;
	ShaderLibrary &operator=(const ShaderLibrary &) = default;
	ShaderLibrary(ShaderLibrary &&) = default;
	ShaderLibrary &operator=(ShaderLibrary &&) = default;
	~ShaderLibrary() = default;

	void Add(const std::string &name, const std::shared_ptr<Shader> &shader);
	void Add(const std::shared_ptr<Shader> &shader);

	std::shared_ptr<Shader> Get(const std::string &name);

	bool Exist(const std::string &name) const;

private:
	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
};

} // namespace Hina
