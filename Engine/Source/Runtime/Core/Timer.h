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

	// Return seconds.
	float ElapsedSeconds() {
		return ElapsedMillis() * 0.001f;
	}

	// Must and can only be called once in the main loop.
	float GetFPS() {
		m_second += ElapsedSeconds();
		++m_frams;

		if(m_second >= 0.5f) {
			m_fps = m_frams / m_second;

			m_frams = 0.0f;
			m_second = 0.0f;
		}

		return m_fps;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

	float m_second = 0.0f;
	float m_frams = 0.0f;
	float m_fps = 0.0f;
};

}
