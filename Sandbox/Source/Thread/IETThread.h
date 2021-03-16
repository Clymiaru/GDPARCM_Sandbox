#pragma once
#include <thread>

class IETThread
{
public:
	IETThread();

	virtual ~IETThread();
	
	void Start();
	static void Sleep(int ms);
protected:
	virtual void Run() = 0;
};
