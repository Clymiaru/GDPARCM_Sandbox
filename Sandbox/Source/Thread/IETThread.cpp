#include "pch.h"
#include <thread>

#include "IETThread.h"

namespace Thread
{
	void IETThread::Start()
	{
		std::thread(&IETThread::Run, this).detach();
	}

	void IETThread::Sleep(const int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
}
