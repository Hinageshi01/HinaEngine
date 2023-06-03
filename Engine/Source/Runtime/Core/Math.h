#pragma once

#include <cassert>
#include <glm/glm.hpp>

namespace Hina
{

class Math final
{
public:
	static float AngularToRadians(const float ang) {
		assert(ang >= 0.0f);
		return ang * 3.1415926535897932f / 180.0f;
	}

	static float RadiansToAngular(const float rad) {
		assert(rad >= 0.0f);
		return rad * 180.0f / 3.1415926535897932f;
	}

	static glm::vec3 GetSphereCoordinate(const glm::vec3 center, const float radius, const float theta, const float phi) {
		return glm::vec3(
			center.x + radius * std::sin(theta) * std::cos(phi),
			center.y + radius * std::sin(theta) * std::sin(phi),
			center.z + radius * std::cos(theta));
	}
};

} // namespace Hina
