#include "pch.h"

#include "Utils/Log/ConsoleLog.h"

auto main(int argc, char** argv) -> int
{
	Utils::ConsoleLog::Init();
	Utils::ConsoleLog::Trace("Trace");
	Utils::ConsoleLog::Info("Info");
	Utils::ConsoleLog::Warn("Warn");
	Utils::ConsoleLog::Error("Error");
}
