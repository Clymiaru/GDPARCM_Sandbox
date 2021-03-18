#pragma once
#include "ConsoleLog.h"

#ifdef ENABLE_ASSERTS
#define ASSERT(x, ...) { if(!(x)) { ::Utils::ConsoleLog::Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ASSERT(x, ...)
#endif
