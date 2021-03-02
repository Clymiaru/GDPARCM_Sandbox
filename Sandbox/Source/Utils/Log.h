#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "TypeAlias.h"

namespace Utils
{
	class Log
	{
	public:
	    static void Init();

	#if DEBUG
	    template <typename... Args>
	    static void Trace(const char* formattedMessage, const Args&... args)
	    {
	        logger->trace(formattedMessage, args...);
	    }

	    template <typename... Args>
	    static void Debug(const char* formattedMessage, const Args&... args)
	    {
	        logger->debug(formattedMessage, args...);
	    }

	    template <typename... Args>
	    static void Info(const char* formattedMessage, const Args&... args)
	    {
	        logger->info(formattedMessage, args...);
	    }

	    template <typename... Args>
	    static void Warn(const char* formattedMessage, const Args&... args)
	    {
	        logger->warn(formattedMessage, args...);
	    }

	    template <typename... Args>
	    static void Error(const char* formattedMessage, const Args&... args)
	    {
	        logger->error(formattedMessage, args...);
	    }

	    template <typename... Args>
	    static void Critical(const char* formattedMessage, const Args&... args)
	    {
	        logger->critical(formattedMessage, args...);
	    }
	#else
		template <typename... Args>
		static void Trace(const char* formattedMessage, const Args&... args)
		{
		}

		template <typename... Args>
		static void Debug(const char* formattedMessage, const Args&... args)
		{
		}

		template <typename... Args>
		static void Info(const char* formattedMessage, const Args&... args)
		{
		}

		template <typename... Args>
		static void Warn(const char* formattedMessage, const Args&... args)
		{
		}

		template <typename... Args>
		static void Error(const char* formattedMessage, const Args&... args)
		{
		}

		template <typename... Args>
		static void Critical(const char* formattedMessage, const Args&... args)
		{
		}
	#endif
	private:
	    static SharedPtr<spdlog::logger> logger;
	};
}

#ifdef ENABLE_ASSERTS
#define ASSERT_ISFALSE(x, ...) { if(!(x)) { ::Utils::Log::Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ASSERT_ISTRUE(x, ...) { if((x)) { ::Utils::Log::Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ASSERT_ISFALSE(x, ...)
#define ASSERT_ISTRUE(x, ...)
#endif