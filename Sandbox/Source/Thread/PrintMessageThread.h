#pragma once
#include "IETThread.h"

class PrintMessageThread : IETThread
{
public:
	PrintMessageThread(std::string toPrint, int interval);
	~PrintMessageThread();
	
protected:
	void Run() override;

private:
	int timeInterval;
	std::string message;
};
