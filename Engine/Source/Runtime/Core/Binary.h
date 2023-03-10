#pragma once

#include <cstdint>

namespace Hina
{

template<class T>
static constexpr inline T BitLeftMove(const uint8_t x) {
	static_assert(
		std::is_unsigned_v<T> && std::is_integral_v<T>,
		"Only support integral.");

	return static_cast<T>(1 << x);
}

#define BIT(x) (1 << x)
#define BIT8(x) BitLeftMove<uint8_t>(x)
#define BIT16(x) BitLeftMove<uint16_t>(x)
#define BIT32(x) BitLeftMove<uint32_t>(x)

} // namespace Hina
