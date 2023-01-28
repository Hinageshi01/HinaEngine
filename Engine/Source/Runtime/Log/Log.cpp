#include "hnpch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Hina
{

std::shared_ptr<spdlog::logger> Log::s_coreLogger;
std::shared_ptr<spdlog::logger> Log::s_applicationLogger;

void Log::Init() {
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_pattern("%^[%T] %n: %v%$");

	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Log/Hina.log", true);
	file_sink->set_pattern("[%T] [%l] %n: %v");

	std::vector<spdlog::sink_ptr> sinks{ console_sink , file_sink };

	s_coreLogger = std::make_shared<spdlog::logger>("HINA", sinks.begin(), sinks.end());
	spdlog::register_logger(s_coreLogger);
	s_coreLogger->set_level(spdlog::level::trace);
	s_coreLogger->flush_on(spdlog::level::trace);

	s_applicationLogger = std::make_shared<spdlog::logger>("APP", sinks.begin(), sinks.end());
	spdlog::register_logger(s_applicationLogger);
	s_applicationLogger->set_level(spdlog::level::trace);
	s_applicationLogger->flush_on(spdlog::level::trace);
}

} // namespace Hina
