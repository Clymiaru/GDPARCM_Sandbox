#include "pch.h"

#include <thread>

#include "Thread/HelloWorldThread.h"

#include "Utils/Log/ConsoleLog.h"

#include "Thread/PrintMessageThread.h"

#include "Utils/Random.h"

void doHelloWorldWithThreads(int iterations)
{
	for (auto i = 0; i < iterations; ++i)
	{
		new Thread::HelloWorldThread(i);
	}
}

void doPrintMessageWithThreads(const std::vector<std::string>& messages)
{
	for (auto i = 0; i < messages.size(); ++i)
	{
		const auto message = messages[i] + " from thread " + std::to_string(i) + "\n";
		new Thread::PrintMessageThread(message, 0);
	}
}

void doRandomPrintMessageWithThreads(const std::vector<std::string>& messages)
{
	for (auto i = 0; i < messages.size(); i++)
	{
		const auto message = messages[i] + " from thread " + std::to_string(i) + "\n";
		new Thread::PrintMessageThread(message, Utils::Random::GetInt(1, 5));
	}
}

auto main(int argc, char** argv) -> int
{
	const std::vector<std::string> messages
	{
		"Hello world",
		"Heya",
		"Mystery",
		"Pudding!",
		"Crystal"
	};
	
	// doHelloWorldWithThreads(20);
	// doPrintMessageWithThreads(messages);
	doRandomPrintMessageWithThreads(messages);
	Thread::IETThread::Sleep(10 * 1000);
}
