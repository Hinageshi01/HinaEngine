#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hina
{

class Log
{
public:
	static void Init();

	static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_coreLogger; }
	static std::shared_ptr<spdlog::logger> &GetApplicationLogger() { return s_applicationLogger; }

private:
	static std::shared_ptr<spdlog::logger> s_coreLogger;
	static std::shared_ptr<spdlog::logger> s_applicationLogger;
};

} // namespace Hina

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
