#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <memory>

namespace Hina
{

class Log
{
public:
	static void Init();

	static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_coreLogger; }
	static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_clientLogger; }

private:
	static std::shared_ptr<spdlog::logger> s_coreLogger;
	static std::shared_ptr<spdlog::logger> s_clientLogger;
};

}

#ifndef NDEBUG

// Core log macros.
#define HN_CORE_TRACE(...) ::Hina::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HN_CORE_INFO(...)  ::Hina::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HN_CORE_WARN(...)  ::Hina::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HN_CORE_ERROR(...) ::Hina::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros.
#define HN_TRACE(...)      ::Hina::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HN_INFO(...)       ::Hina::Log::GetClientLogger()->info(__VA_ARGS__)
#define HN_WARN(...)       ::Hina::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HN_ERROR(...)      ::Hina::Log::GetClientLogger()->error(__VA_ARGS__)

#else

// We don't need log in release mode.
#define HN_CORE_TRACE(...)
#define HN_CORE_INFO(...)
#define HN_CORE_WARN(...)
#define HN_CORE_ERROR(...)
#define HN_CORE_FATAL(...)
#define HN_TRACE(...)
#define HN_INFO(...)
#define HN_WARN(...)
#define HN_ERROR(...)
#define HN_FATAL(...)

#endif
