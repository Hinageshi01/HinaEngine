#pragma once

#include <string>

namespace Hina
{

class NameComponent final
{
public:
	NameComponent(const std::string &name) : m_name(name) {}
	NameComponent(std::string &&name) : m_name(name) {}

	NameComponent() = default;
	NameComponent &operator=(const NameComponent &) = default;
	NameComponent(const NameComponent &) = default;
	NameComponent &operator=(NameComponent &&) = default;
	NameComponent(NameComponent &&) = default;
	~NameComponent() = default;

	void SetName(const std::string &name) { m_name = name; }
	void SetName(std::string &&name) { m_name = name; }

	const std::string &GetName() const { return m_name; }
	std::string &GetName() { return m_name; }

private:
	std::string m_name;
};

} // namespace Hina
