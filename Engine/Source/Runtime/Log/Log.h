#pragma once

#include <glm/gtx/string_cast.hpp>

// This ignores all warnings raised inside External headers.
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Hina
{

class Log final
{
public:
	static void Init();

	static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_coreLogger; }
	static std::shared_ptr<spdlog::logger> &GetApplicationLogger() { return s_applicationLogger; }

	static const std::ostringstream &GetSpdOutput() { return m_oss; }
	static void ClearBuffer() { m_oss.str(""); }

private:
	static std::shared_ptr<spdlog::logger> s_coreLogger;
	static std::shared_ptr<spdlog::logger> s_applicationLogger;

	// Note that m_oss will be cleared after ImGuiLog::AddSpdLog be called.
	static std::ostringstream m_oss;
};

} // namespace Hina

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::vec<L, T, Q> &vector) {
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, const glm::mat<C, R, T, Q> &matrix) {
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream &operator<<(OStream &os, glm::qua<T, Q> quaternion) {
	return os << glm::to_string(quaternion);
}

#ifndef NDEBUG

// Core log macros.
#define HN_CORE_TRACE(...) ::Hina::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HN_CORE_INFO(...)  ::Hina::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HN_CORE_WARN(...)  ::Hina::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HN_CORE_ERROR(...) ::Hina::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HN_CORE_FATAL(...) ::Hina::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros.
#define HN_APP_TRACE(...)  ::Hina::Log::GetApplicationLogger()->trace(__VA_ARGS__)
#define HN_APP_INFO(...)   ::Hina::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define HN_APP_WARN(...)   ::Hina::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define HN_APP_ERROR(...)  ::Hina::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define HN_APP_FATAL(...)  ::Hina::Log::GetApplicationLogger()->critical(__VA_ARGS__)

// Runtime assert.
#define HN_CORE_ASSERT(x, ...) { if(!(x)) { HN_CORE_ERROR("Assert failed: {0}", __VA_ARGS__); } }
#define HN_APP_ASSERT(x, ...)  { if(!(x)) { HN_APP_ERROR("Assert failed: {0}", __VA_ARGS__); } }

#else

// We don't need log in release mode.
#define HN_CORE_TRACE(...)
#define HN_CORE_INFO(...)
#define HN_CORE_WARN(...)
#define HN_CORE_ERROR(...)
#define HN_CORE_FATAL(...)
#define HN_APP_TRACE(...)
#define HN_APP_INFO(...)
#define HN_APP_WARN(...)
#define HN_APP_ERROR(...)
#define HN_APP_FATAL(...)

#define HN_CORE_ASSERT(x, ...)
#define HN_APP_ASSERT(x, ...)

#endif
