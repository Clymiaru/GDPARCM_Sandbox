#include "pch.h"
#include "Stopwatch.h"

Stopwatch::Stopwatch():
        start{std::chrono::time_point<std::chrono::steady_clock>()},
        end{std::chrono::time_point<std::chrono::steady_clock>()},
        duration{}
{
	start = std::chrono::steady_clock::now();
}

Stopwatch::~Stopwatch()
{
	end = std::chrono::steady_clock::now();
	duration = end - start;

	std::cout << "Duration: " << duration.count() << "us\n";
}
