#pragma once
#include <chrono>

class Stopwatch final
{
public:
	Stopwatch();
	~Stopwatch();
private:
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<float, std::micro> duration;
	std::chrono::steady_clock highResClock;
};