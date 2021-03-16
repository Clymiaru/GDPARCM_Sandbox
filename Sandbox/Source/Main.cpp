#include "pch.h"

#include <thread>
#include "Utils/Log/ConsoleLog.h"

#include "Thread/PrintMessageThread.h"

auto main(int argc, char** argv) -> int
{
	for (auto i = 0; i < 20; ++i)
	{
		std::string message = "Hello " + std::to_string(i);
		auto thread = new PrintMessageThread(message, 0);
	}
	
	IETThread::Sleep(2000);
}
