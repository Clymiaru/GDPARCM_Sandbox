#include "pch.h"
#include "ConsoleLog.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Utils/TypeAlias.h"

SharedPtr<spdlog::logger> Utils::ConsoleLog::logger;

void Utils::ConsoleLog::Init()
{
#if DEBUG
	logger = spdlog::stdout_color_mt("CONSOLE_LOG");
	logger->set_level(spdlog::level::trace);
	logger->set_pattern("%^[%T] %n: %v%$");
#endif
}
