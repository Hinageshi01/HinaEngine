#pragma once

#include <glm/glm.hpp>

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace Hina
{

using PropertyMapKey = std::string;

class PropertyMap final
{
public:
	PropertyMap() = default;
	PropertyMap(const PropertyMap &) = delete;
	PropertyMap &operator=(const PropertyMap &) = delete;
	PropertyMap(PropertyMap &&) = default;
	PropertyMap &operator=(PropertyMap &&) = default;
	~PropertyMap() = default;

	template<typename T>
	void Add(const PropertyMapKey &key, const T &value) {
		CheckType<T>();

		if(!Exist(key)) {
			SetValue(key, value);
			m_keySet.insert(key);
		}
		else {
			HN_CORE_WARN("PropertyMap key alerady exists!");
		}
	}

	template<typename T>
	void Set(const PropertyMapKey &key, const T &value) {
		CheckType<T>();

		if(Exist(key)) {
			SetValue(key, value);
		}
		else {
			HN_CORE_WARN("PropertyMap key does not exists!");
		}
	}

	template<typename T>
	std::optional<T> Get(const PropertyMapKey &key) const {
		CheckType<T>();

		if(Exist(key)) {
			if constexpr(std::is_same_v<T, std::string>) {
				return m_stringProperty.at(key);
			}
			else if constexpr(std::is_same_v<T, uint32_t> || std::is_same_v<T, bool> || std::is_same_v<T, int> || std::is_same_v<T, float>) {
				return reinterpret_cast<const T &>(m_4byteProperty.at(key));
			}
			else if constexpr(std::is_same_v<T, uint64_t> || std::is_same_v<T, double> || std::is_same_v<T, glm::vec2>) {
				return reinterpret_cast<const T &>(m_8byteProperty.at(key));
			}
			else if constexpr(std::is_same_v<T, glm::vec3>) {
				return m_12byteProperty.at(key);
			}
			else if constexpr(std::is_same_v<T, glm::vec4>) {
				return m_16byteProperty.at(key);
			}
			else {
				HN_CORE_WARN("PropertyMap key does not exists!");
				return std::nullopt;
			}
		}
		else {
			return std::nullopt;
		}
	}

	bool Exist(const PropertyMapKey &key) const {
		return !!m_keySet.count(key);
	}

	void Remove(const PropertyMapKey &key) {
		if(Exist(key)) {
			m_keySet.erase(key);
			m_stringProperty.erase(key);
			m_4byteProperty.erase(key);
			m_8byteProperty.erase(key);
			m_12byteProperty.erase(key);
			m_16byteProperty.erase(key);
		}
		else {
			HN_CORE_WARN("PropertyMap key does not exists!");
		}
	}

	void Clear() {
		m_keySet.clear();
		m_stringProperty.clear();
		m_4byteProperty.clear();
		m_8byteProperty.clear();
		m_12byteProperty.clear();
		m_16byteProperty.clear();
	}

private:
	template<typename T>
	void SetValue(const PropertyMapKey &key, const T &value) {
		if constexpr(std::is_same_v<T, std::string>) {
			m_stringProperty[key] = value;
		}
		else if constexpr(std::is_same_v<T, uint32_t> || std::is_same_v<T, bool> || std::is_same_v<T, int> || std::is_same_v<T, float>) {
			m_4byteProperty[key] = reinterpret_cast<const uint32_t &>(value);
		}
		else if constexpr(std::is_same_v<T, uint64_t> || std::is_same_v<T, double> || std::is_same_v<T, glm::vec2>) {
			m_8byteProperty[key] = reinterpret_cast<const uint64_t &>(value);
		}
		else if constexpr(std::is_same_v<T, glm::vec3>) {
			m_12byteProperty[key] = value;
		}
		else if constexpr(std::is_same_v<T, glm::vec4>) {
			m_16byteProperty[key] = value;
		}
	}

	template<typename T>
	void CheckType() const {
		static_assert((
			std::is_same_v<T, std::string> ||

			std::is_same_v<T, uint32_t> ||
			std::is_same_v<T, bool> ||
			std::is_same_v<T, int> ||
			std::is_same_v<T, float> ||

			std::is_same_v<T, uint64_t> ||
			std::is_same_v<T, double> ||

			std::is_same_v<T, glm::vec2> ||
			std::is_same_v<T, glm::vec3> ||
			std::is_same_v<T, glm::vec4>) &&

			"PropertyMap unsupport type!"
		);
	}

	std::unordered_map<PropertyMapKey, std::string> m_stringProperty;
	std::unordered_map<PropertyMapKey, uint32_t>    m_4byteProperty;
	std::unordered_map<PropertyMapKey, uint64_t>    m_8byteProperty;
	std::unordered_map<PropertyMapKey, glm::vec3>   m_12byteProperty;
	std::unordered_map<PropertyMapKey, glm::vec4>   m_16byteProperty;

	std::unordered_set<PropertyMapKey> m_keySet;
};

static_assert(sizeof(int) == sizeof(uint32_t));
static_assert(sizeof(float) == sizeof(uint32_t));
static_assert(sizeof(double) == sizeof(uint64_t));

static_assert(sizeof(glm::vec2) == sizeof(uint32_t) * 2);
static_assert(sizeof(glm::vec3) == sizeof(uint32_t) * 3);
static_assert(sizeof(glm::vec4) == sizeof(uint32_t) * 4);

} // namespace Hina
