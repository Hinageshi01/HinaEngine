#pragma once

#include <chrono>

namespace Hina
{

class Timer
{
public:
	Timer() {
		Reset();
	}

	Timer(const Timer &) = default;
	Timer &operator=(const Timer &) = default;
	Timer(Timer &&) = default;
	Timer &operator=(Timer &&) = default;
	~Timer() = default;
	
	void Reset() {
		m_start = std::chrono::high_resolution_clock::now();
	}

	// Return milliseconds.
	float ElapsedMillis() {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now() - m_start).count() * 0.001f * 0.001f;
	}

	float ElapsedSeconds() {
		return ElapsedMillis() * 0.001f;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};

}
