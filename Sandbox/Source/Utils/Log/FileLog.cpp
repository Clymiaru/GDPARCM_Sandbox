#include "pch.h"
#include "FileLog.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

List<SharedPtr<spdlog::logger>> Utils::FileLog::fileLoggers;

namespace Utils
{
	SharedPtr<spdlog::logger> FileLog::GetExistingFileLogger(const std::string& filename)
	{
		const auto toFindLoggerName = FILE_LOG_PREFIX + filename;
		for (auto& fileLogger : fileLoggers)
		{
			if (fileLogger->name() == toFindLoggerName)
			{
				return fileLogger;
			}
		}
		return nullptr;
	}

	SharedPtr<spdlog::logger> FileLog::CreateFileLogger(const std::string& filename)
	{
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/" + filename);
		auto logger = createSharedPtr<spdlog::logger>(FILE_LOG_PREFIX + filename, sink);
		logger->set_level(spdlog::level::trace);
		logger->set_pattern("%^[%T]\n\t%v%$");
		return logger;
	}
}
