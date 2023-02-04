#pragma once

#include "Renderer/Shader.h"

namespace Hina
{

class ShaderLibrary
{
public:
	void Add(const std::string &name, const std::shared_ptr<Shader> &shader);
	void Add(const std::shared_ptr<Shader> &shader);

	std::shared_ptr<Shader> Get(const std::string &name);

	bool Exists(const std::string &name) const;

private:
	std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
};

} // namespace Hina
