#include "pch.h"

#include "Utils/Log/ConsoleLog.h"
#include <thread>

class Stopwatch
{
public:
	Stopwatch() :
        start{std::chrono::time_point<std::chrono::steady_clock>()},
        end{std::chrono::time_point<std::chrono::steady_clock>()},
        duration{}
	{
		start = std::chrono::steady_clock::now();
	}

	~Stopwatch()
	{
		end = std::chrono::steady_clock::now();
		duration = end - start;

		std::cout << "Duration: " << duration.count() << "us\n";
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<float, std::micro> duration;
	std::chrono::steady_clock highResClock;
	
};

void testFunction(int threadID)
{
	std::cout << "Hello from thread " << threadID << "\n";
}

auto main(int argc, char** argv) -> int
{
	Utils::ConsoleLog::Init();
	Utils::ConsoleLog::Trace("Trace");
	Utils::ConsoleLog::Info("Info");
	Utils::ConsoleLog::Warn("Warn");
	Utils::ConsoleLog::Error("Error");

	for (auto i = 0; i < 20; ++i)
	{
		std::thread t(testFunction, i);
		t.detach();
		Sleep(1000);
	}
	
}
