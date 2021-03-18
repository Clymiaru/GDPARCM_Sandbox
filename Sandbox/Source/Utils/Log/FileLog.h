#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "Utils/TypeAlias.h"

namespace Utils
{
	class FileLog
	{
	public:
		template <typename... Args>
		static void Log(const std::string& filename, const char* formattedMessage, const Args&... args)
		{
			auto logger = GetExistingFileLogger(filename);

			if (logger == nullptr)
			{
				logger = CreateFileLogger(filename);
				fileLoggers.push_back(logger);
			}

			logger->trace(formattedMessage, args...);
		}

	private:
		static SharedPtr<spdlog::logger> GetExistingFileLogger(const std::string& filename);

		static SharedPtr<spdlog::logger> CreateFileLogger(const std::string& filename);

		inline static const std::string FILE_LOG_PREFIX = "FILE_LOG_";

		static List<SharedPtr<spdlog::logger>> fileLoggers;
	};
}
