#include "pch.h"
#include "PrintMessageThread.h"

PrintMessageThread::PrintMessageThread(std::string toPrint, int interval) :
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
		IETThread::Sleep(timeInterval);
	}
}
