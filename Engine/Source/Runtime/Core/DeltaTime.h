#pragma once

namespace Hina
{

class DeltaTime final
{
public:
	DeltaTime(float time = 0.0f) : m_time(time) {}

	DeltaTime() = default;
	DeltaTime(const DeltaTime &) = default;
	DeltaTime &operator=(const DeltaTime &) = default;
	DeltaTime(DeltaTime &&) = default;
	DeltaTime &operator=(DeltaTime &&) = default;
	
	inline operator float() const { return m_time; }

	inline float GetSeconds() const { return m_time; }
	inline float GetMilliseconds() const { return m_time * 1000.0f; }

private:
	float m_time = 0.0f;
};

} // namespace Hina
