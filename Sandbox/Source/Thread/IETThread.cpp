﻿#include "pch.h"
#include "IETThread.h"

IETThread::IETThread()
{
}

IETThread::~IETThread()
{
}

void IETThread::Start()
{
	std::thread(&IETThread::Run, this).detach();
}

void IETThread::Sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

