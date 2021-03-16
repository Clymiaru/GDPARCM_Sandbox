#include "pch.h"
#include "PrintMessageThread.h"

namespace Thread
{
	PrintMessageThread::PrintMessageThread(std::string toPrint, const int interval) :
		timeInterval{interval},
		message{std::move(toPrint)}
	{
		Start();
	}

	PrintMessageThread::~PrintMessageThread()
	{
	}

	void PrintMessageThread::Run()
	{
		while (true)
		{
			std::cout << message << "\n";
			Sleep(timeInterval);
		}
	}
}
