#pragma once
#include <Thread/IETThread.h>

namespace Thread
{
	class HelloWorldThread final : IETThread
	{
	public:
		explicit HelloWorldThread(int id);
		~HelloWorldThread() override = default;

		HelloWorldThread(const HelloWorldThread& other) = delete;
		HelloWorldThread(HelloWorldThread&& other) noexcept = delete;
		auto operator=(const HelloWorldThread& other) -> HelloWorldThread& = delete;
		auto operator=(HelloWorldThread&& other) noexcept -> HelloWorldThread& = delete;

	private:
		void Run() override;
		int threadID;
	};
}
