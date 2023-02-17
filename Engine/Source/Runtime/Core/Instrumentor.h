#pragma once

#include "Log/Log.h"

namespace Hina
{

using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct ProfileResult
{
	std::string m_name;

	FloatingPointMicroseconds m_start;
	std::chrono::microseconds m_elapsedTime;
	std::thread::id m_threadID;
};

struct InstrumentationSession
{
	std::string m_name;
};

class Instrumentor
{
public:
	Instrumentor(const Instrumentor &) = delete;
	Instrumentor(Instrumentor &&) = delete;

	void BeginSession(const std::string &name, const std::string &filepath = "results.json") {
		std::lock_guard lock(m_mutex);
		if(m_currentSession) {
			// If there is already a current session, then close it before beginning new one.
			// Subsequent profiling output meant for the original session will end up in the
			// newly opened session instead.  That's better than having badly formatted
			// profiling output.
			if(Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
			{
				HN_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_currentSession->m_name);
			}
			InternalEndSession();
		}
		m_outputStream.open(filepath);

		if(m_outputStream.is_open()) {
			m_currentSession = new InstrumentationSession({ name });
			WriteHeader();
		}
		else {
			if(Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
			{
				HN_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
			}
		}
	}

	void EndSession() {
		std::lock_guard lock(m_mutex);
		InternalEndSession();
	}

	void WriteProfile(const ProfileResult &result) {
		std::stringstream json;

		json << std::setprecision(3) << std::fixed;
		json << ",{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << (result.m_elapsedTime.count()) << ',';
		json << "\"name\":\"" << result.m_name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << result.m_threadID << ",";
		json << "\"ts\":" << result.m_start.count();
		json << "}";

		std::lock_guard lock(m_mutex);
		if(m_currentSession) {
			m_outputStream << json.str();
			m_outputStream.flush();
		}
	}

	static Instrumentor &Get() {
		static Instrumentor instance;
		return instance;
	}

private:
	Instrumentor()
		: m_currentSession(nullptr) {}

	~Instrumentor() {
		EndSession();
	}

	void WriteHeader() {
		m_outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
		m_outputStream.flush();
	}

	void WriteFooter() {
		m_outputStream << "]}";
		m_outputStream.flush();
	}

	// Note: you must already own lock on m_Mutex before
	// calling InternalEndSession()
	void InternalEndSession() {
		if(m_currentSession) {
			WriteFooter();
			m_outputStream.close();
			delete m_currentSession;
			m_currentSession = nullptr;
		}
	}

private:
	std::mutex m_mutex;
	InstrumentationSession *m_currentSession;
	std::ofstream m_outputStream;
};

class InstrumentationTimer
{
public:
	InstrumentationTimer(const char *name)
		: m_name(name), m_stopped(false) {
		m_startTimepoint = std::chrono::steady_clock::now();
	}

	~InstrumentationTimer() {
		if(!m_stopped)
			Stop();
	}

	void Stop() {
		auto endTimepoint = std::chrono::steady_clock::now();
		auto highResStart = FloatingPointMicroseconds{ m_startTimepoint.time_since_epoch() };
		auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() -
			std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch();

		Instrumentor::Get().WriteProfile({ m_name, highResStart, elapsedTime, std::this_thread::get_id() });

		m_stopped = true;
	}

private:
	const char *m_name;
	std::chrono::time_point<std::chrono::steady_clock> m_startTimepoint;
	bool m_stopped;
};

namespace InstrumentorUtils
{

template <size_t N>
struct ChangeResult
{
	char m_data[N];
};

template <size_t N, size_t K>
constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K]) {
	ChangeResult<N> result = {};

	size_t srcIndex = 0;
	size_t dstIndex = 0;
	while(srcIndex < N) {
		size_t matchIndex = 0;
		while(matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
			matchIndex++;
		if(matchIndex == K - 1)
			srcIndex += matchIndex;
		result.m_data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
		srcIndex++;
	}
	return result;
}

} // namespace InstrumentorUtils

} // namespace Hina

#define HN_PROFILE 0

#if HN_PROFILE

	#define HN_PROFILE_BEGIN_SESSION(name, filepath) ::Hina::Instrumentor::Get().BeginSession(name, filepath)
	#define HN_PROFILE_END_SESSION() ::Hina::Instrumentor::Get().EndSession()
	#define HN_PROFILE_SCOPE_LINE(name, line) constexpr auto fixedName##line = ::Hina::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
												   ::Hina::InstrumentationTimer timer##line(fixedName##line.m_data)
	#define HN_PROFILE_SCOPE(name) HN_PROFILE_SCOPE_LINE(name, __LINE__)
	#define HN_PROFILE_FUNCTION() HN_PROFILE_SCOPE(__FUNCSIG__)

#else

	#define HN_PROFILE_BEGIN_SESSION(name, filepath)
	#define HN_PROFILE_END_SESSION()
	#define HN_PROFILE_SCOPE(name)
	#define HN_PROFILE_FUNCTION()

#endif
