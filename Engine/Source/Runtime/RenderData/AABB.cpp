#include "hnpch.h"
#include "AABB.h"

namespace Hina
{

namespace
{

inline bool operator>(const glm::vec3 &a, const glm::vec3 &b) {
	return (a.x >= b.x) && (a.y >= b.y) && (a.z >= b.z) &&
		((a.x > b.x) || (a.y > b.y) || (a.z > b.z));
}

inline bool operator<(const glm::vec3 &a, const glm::vec3 &b) {
	return (a.x <= b.x) && (a.y <= b.y) && (a.z <= b.z) &&
		((a.x < b.x) || (a.y < b.y) || (a.z < b.z));
}

}

glm::vec3 AABB::GetCentre() const {
	if(IsValid()) {
		return (m_max + m_min) / 2.0f;
	}
	else {
		HN_CORE_ERROR("Bounding box invalid!");
		return { 0.0f, 0.0f , 0.0f };
	}
}

float AABB::GetSize() const {
	if(IsValid()) {
		const glm::vec3 diagonal = m_max - m_min;
		return std::sqrtf(diagonal.x * diagonal.x + diagonal.y * diagonal.y + diagonal.z * diagonal.z);
	}
	else {
		HN_CORE_ERROR("Bounding box invalid!");
		return 0.0f;
	}
}

void AABB::AddPoint(const glm::vec3 &point) {
	if(point > m_max) {
		m_max = point;
	}
	else if(point < m_min) {
		m_min = point;
	}
}

bool AABB::IsValid() const {
	return m_max > m_min;
}

} // namespace Hina
