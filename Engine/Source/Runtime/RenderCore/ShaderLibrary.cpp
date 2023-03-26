#include "hnpch.h"
#include "ShaderLibrary.h"

namespace Hina
{

void ShaderLibrary::Add(const std::string &name, const std::shared_ptr<Shader> &shader) {
	if(!Exist(name)) {
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
	if(Exist(name)) {
		return m_shaders[name];
	}
	else {
		HN_CORE_ERROR("Shader {0} not found!", name);
		return nullptr;
	}
}

bool ShaderLibrary::Exist(const std::string &name) const {
	return m_shaders.find(name) != m_shaders.end();
}

bool ShaderLibrary::Exist(std::string &&name) const {
	return m_shaders.find(name) != m_shaders.end();
}

} // namespace Hina
