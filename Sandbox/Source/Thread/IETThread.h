#pragma once

namespace Thread
{
	class IETThread
	{
	public:
		IETThread() = default;
		virtual ~IETThread() = default;

		IETThread(const IETThread& other) = delete;
		IETThread(IETThread&& other) noexcept = delete;
		auto operator=(const IETThread& other) -> IETThread& = delete;
		auto operator=(IETThread&& other) noexcept -> IETThread& = delete;

		void Start();
		static void Sleep(int ms);

	protected:
		virtual void Run() = 0;

	private:
		bool isRunning;

	};
}
