#include "pch.h"
#include "HelloWorldThread.h"

namespace Thread
{
	HelloWorldThread::HelloWorldThread(const int id)
	{
		threadID = id;
		Start();
	}

	void HelloWorldThread::Run()
	{
		std::cout << "Hello world from thread " << threadID << "\n";
	}
}
