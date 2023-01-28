#pragma once

namespace Hina
{

template<class T>
constexpr T BitLeftMove(const uint8_t x) {
	static_assert(
		!std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer &&
		"Only support unsigned integer.");
	return static_cast<T>(1 << x);
}

#define BIT(x) (1 << x)
#define BIT8(x) BitLeftMove<uint8_t>(x)
#define BIT16(x) BitLeftMove<uint16_t>(x)
#define BIT32(x) BitLeftMove<uint32_t>(x)

} // namespace Hina
