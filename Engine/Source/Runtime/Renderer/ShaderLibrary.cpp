#include "hnpch.h"
#include "ShaderLibrary.h"

namespace Hina
{

void ShaderLibrary::Add(const std::string &name, const std::shared_ptr<Shader> &shader) {
	if(!Exists(name)) {
		m_shaders[name] = shader;
	}
	else {
		HN_CORE_ERROR("Shader {0} already exists!", name);
	}
}

void ShaderLibrary::Add(const std::shared_ptr<Shader> &shader) {
	const std::string &name = shader->GetName();
	Add(name, shader);
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string &name) {
	if(Exists(name)) {
		return m_shaders[name];
	}
	else {
		HN_CORE_ERROR("Shader {0} not found!", name);
	}
}

bool ShaderLibrary::Exists(const std::string &name) const {
	return m_shaders.find(name) != m_shaders.end();
}

} // namespace Hina
