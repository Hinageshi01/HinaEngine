#pragma once

#include <glm/glm.hpp>

namespace Hina
{

class AABB final
{
public:
	AABB(const glm::vec3 max, const glm::vec3 min)
		: m_max(max), m_min(min) {}

	AABB() = default;
	AABB(const AABB &) = default;
	AABB &operator=(const AABB &) = default;
	AABB(AABB &&) = default;
	AABB &operator=(AABB &&) = default;
	~AABB() = default;

	void SetMax(const glm::vec3 &max) { m_max = max; }
	glm::vec3 &GetMax() { return m_max; }
	const glm::vec3 &GetMax() const { return m_max; }

	void SetMin(const glm::vec3 &min) { m_min = min; }
	glm::vec3 &GetMin() { return m_min; }
	const glm::vec3 &GetMin() const { return m_min; }

	void AddPoint(const glm::vec3 &point);
	glm::vec3 GetCentre() const;
	float GetSize() const;

private:
	bool IsValid() const;

	glm::vec3 m_max = { 0.0f, 0.0f , 0.0f };
	glm::vec3 m_min = { 0.0f, 0.0f , 0.0f };
};

} // namespace Hina
