#pragma once
#include "IETThread.h"

namespace Thread
{
	class PrintMessageThread final : IETThread
	{
	public:
		PrintMessageThread(int id, std::string toPrint, int interval);
		~PrintMessageThread() override = default;

		PrintMessageThread(const PrintMessageThread& other) = delete;
		PrintMessageThread(PrintMessageThread&& other) noexcept = delete;
		auto operator=(const PrintMessageThread& other) -> PrintMessageThread& = delete;
		auto operator=(PrintMessageThread&& other) noexcept -> PrintMessageThread& = delete;

	private:
		void Run() override;

		int threadID;
		int timeInterval;
		std::string message;
	};
}
