#include "pch.h"

#include "Utils/Log.h"

auto main(int argc, char** argv) -> int
{
	Utils::Log::Init();
	Utils::Log::Info("Test");
}
