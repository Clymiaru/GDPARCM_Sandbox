#include "pch.h"
#include "PrintMessageThread.h"

namespace Thread
{
	PrintMessageThread::PrintMessageThread(const int id, std::string toPrint, const int interval) :
		threadID{id},
		timeInterval{interval},
		message{std::move(toPrint)}
	{
		message += " from thread " + std::to_string(threadID) + "\n";
		Start();
	}

	void PrintMessageThread::Run()
	{
		while (true)
		{
			std::cout << message;
			Sleep(timeInterval);
		}
	}
}
