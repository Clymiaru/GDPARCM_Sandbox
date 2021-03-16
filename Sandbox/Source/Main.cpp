#include "pch.h"

#include <thread>

#include "Thread/HelloWorldThread.h"

#include "Utils/Log/ConsoleLog.h"

#include "Thread/PrintMessageThread.h"

#include "Utils/Random.h"

void doHelloWorldWithThreads(const int iterations)
{
	for (auto i = 0; i < iterations; ++i)
	{
		new Thread::HelloWorldThread(i);
	}
}

void doPrintMessageWithThreads(const std::vector<std::string>& messages)
{
	for (size_t i = 0; i < messages.size(); ++i)
	{
		new Thread::PrintMessageThread(i, messages[i], 0);
	}
}

void doRandomPrintMessageWithThreads(const std::vector<std::string>& messages)
{
	const auto minRandRange = 1;
	const auto maxRandRange = 5;
	
	for (size_t i = 0; i < messages.size(); i++)
	{
		new Thread::PrintMessageThread(i, messages[i], 
								Utils::Random::GetInt(minRandRange, maxRandRange));
	}
}

auto main(int argc, char** argv) -> int
{
	const std::vector<std::string> messages
	{
		"Hello world",
		"Kira, Kira, Mahorin~",
		"Labyrinth",
		"Pudding!",
		"Crystal",
		"If we put a fence, we'll have more de-fence!",
		"Blubberino",
		"Time flies like an arrow rain",
		"A stitch in thyme",
		"A little learning is an arduous thing",
		"Rags to britches",
		"Jealous Nyatt",
		"Ultra Misogi Trap!!",
		"Trapology 101",
		"Pudding Paradise",
		"The path of Pudding",
		"Pudding Knight!",
		"Nyan Justice",
		"Ame-Same",
		"Sus!",
	};
	
	// doHelloWorldWithThreads(20);
	// doPrintMessageWithThreads(messages);
	doRandomPrintMessageWithThreads(messages);
	Thread::IETThread::Sleep(10 * 1000);
}
