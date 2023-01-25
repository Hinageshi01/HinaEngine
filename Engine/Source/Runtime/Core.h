#pragma once

#ifdef HN_PLATFORM_WIN
	#ifdef HN_BUILD_DLL
		#define HN_API __declspec(dllexport)
	#else
		#define HN_API __declspec(dllimport)
	#endif
#else
	#error Hina only support windows!
#endif
