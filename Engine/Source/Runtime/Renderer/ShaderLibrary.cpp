#include "hnpch.h"
#include "ShaderLibrary.h"

namespace Hina
{

void ShaderLibrary::Add(const std::string &name, const std::shared_ptr<Shader> &shader) {
	HN_CORE_ASSERT(!Exists(name), "Shader already exists!");
	m_shaders[name] = shader;
}

void ShaderLibrary::Add(const std::shared_ptr<Shader> &shader) {
	auto &name = shader->GetName();
	Add(name, shader);
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string &name) {
	HN_CORE_ASSERT(Exists(name), "Shader not found!");
	return m_shaders[name];
}

bool ShaderLibrary::Exists(const std::string &name) const {
	return m_shaders.find(name) != m_shaders.end();
}

} // namespace Hina
