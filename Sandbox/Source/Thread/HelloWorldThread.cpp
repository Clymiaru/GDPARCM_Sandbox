#include "pch.h"
#include "HelloWorldThread.h"

HelloWorldThread::HelloWorldThread(int id)
{
	this->id = id;
	Start();
}

HelloWorldThread::~HelloWorldThread()
{
}

void HelloWorldThread::Run()
{
	std::cout << "Hello world from thread " << id << "\n";
}
