#pragma once
#include "IETThread.h"

namespace Thread
{
	class PrintMessageThread final : IETThread
	{
	public:
		PrintMessageThread(std::string toPrint, int interval);

		~PrintMessageThread();

	private:
		void Run() override;

		int timeInterval;
		std::string message;
	};
}
