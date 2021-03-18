#pragma once
#include <spdlog/spdlog.h>

#include "Utils/TypeAlias.h"

namespace Utils
{
	class ConsoleLog
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
#else
		template <typename... Args>
		static void Trace(const char* formattedMessage, const Args&... args)
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
#endif
	private:
		static SharedPtr<spdlog::logger> logger;
	};
}
