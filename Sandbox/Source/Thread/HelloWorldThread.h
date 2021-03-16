#pragma once
#include <Thread/IETThread.h>

class HelloWorldThread : IETThread
{
public:
	HelloWorldThread(int threadID);
	~HelloWorldThread();

protected:
	void Run() override;

	int id;
};
