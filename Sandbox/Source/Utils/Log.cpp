#include "pch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

#include "TypeAlias.h"

SharedPtr<spdlog::logger> Utils::Log::logger;

void Utils::Log::Init()
{
#if DEBUG
    spdlog::set_pattern("%^[%T] %n: %v%$");
    logger = spdlog::stdout_color_mt("APP");
    logger->set_level(spdlog::level::trace);
#endif
}
