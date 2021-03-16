#pragma once
#include <Thread/IETThread.h>

namespace Thread
{
	class HelloWorldThread final : IETThread
	{
	public:
		explicit HelloWorldThread(int id);

		~HelloWorldThread();

	private:
		void Run() override;

		int threadID;
	};
}
