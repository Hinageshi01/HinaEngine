#include "hnpch.h"
#include "Log.h"

#pragma warning(push, 0)
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#pragma warning(pop)

namespace Hina
{

std::shared_ptr<spdlog::logger> Log::s_coreLogger;
std::shared_ptr<spdlog::logger> Log::s_applicationLogger;
std::ostringstream Log::m_oss;

void Log::Init() {
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_pattern("%^[%T] %n: %v%$");

	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Hina.log", true);
	fileSink->set_pattern("[%T] [%l] %n: %v");

	auto ossSink = std::make_shared<spdlog::sinks::ostream_sink_mt>(m_oss);
	ossSink->set_pattern("[%T] [%n] [%l]: %v");

	std::vector<spdlog::sink_ptr> sinks{ consoleSink , fileSink, ossSink };

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
