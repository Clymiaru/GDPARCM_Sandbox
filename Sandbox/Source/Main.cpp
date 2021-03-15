#include "pch.h"


#include <queue>
#include <string>

#include "Utils/Log/ConsoleLog.h"
#include "Utils/Log/FileLog.h"

struct Process
{
	std::string ProcessID;
	int ArrivalTime;
	int CPUBurst;
	int StartTime;
	int EndTime;
	int WaitingTime;
	bool HasStarted;

	Process(std::string name, int arrivalTime, int cpuBurst) :
		ProcessID{name},
		ArrivalTime{arrivalTime},
		CPUBurst{cpuBurst},
		StartTime{0},
		EndTime{0},
		WaitingTime{0},
		HasStarted{false}
	{
	}

	auto Start(int currentTime)
	{
		if (!HasStarted)
		{
			StartTime = currentTime;
			HasStarted = true;
		}
	}

	auto Use(int currentTime) -> Process*
	{
		CPUBurst--;
		if (CPUBurst == 0)
		{
			EndTime = currentTime;
			return nullptr;
		}
		return this;
	}

	void Print() const
	{
		Utils::ConsoleLog::Info("{0} | Start Time: {1} | End Time: {2} | Waiting Time: {3}", ProcessID, StartTime, EndTime, WaitingTime);
	}
};

auto changeProcess(std::vector<Process*>* readyQueue) -> Process*
{
	auto* process = readyQueue->front();
	readyQueue->erase(readyQueue->begin());
	return process;
}

void printProcessList(const std::vector<Process*> processes)
{
	auto averageWaitingTime = 0.0f;
	Utils::ConsoleLog::Info("Processes");
	for (auto process : processes)
	{
		process->Print();
		averageWaitingTime += process->WaitingTime;
	}

	averageWaitingTime /= processes.size();
	Utils::ConsoleLog::Info("Average Waiting Time: {0}", averageWaitingTime);
	
}

void updateArrivalTime(const std::vector<Process*>& processes, std::vector<Process*>* readyQueue)
{
	for (auto* process : processes)
	{
		if (process->ArrivalTime == 0)
		{
			readyQueue->push_back(process);
		}
		process->ArrivalTime--;
	}
}

void updateWaitingTime(const std::vector<Process*>& readyQueue)
{
	for (auto* process : readyQueue)
	{
		process->WaitingTime++;
	}
}

void firstComeFirstServe(const std::vector<Process> processList)
{
	auto currentTime = 0;
	std::vector<Process*> processes;
	std::vector<Process*> readyQueue;

	Process* currentProcess = nullptr;

	for (auto process : processList)
	{
		processes.push_back(new Process(process.ProcessID, process.ArrivalTime, process.CPUBurst));
	}

	do
	{
		updateArrivalTime(processes, &readyQueue);

		if (currentProcess != nullptr)
		{
			currentProcess = currentProcess->Use(currentTime);
		}

		if (currentProcess == nullptr && !readyQueue.empty())
		{
			currentProcess = changeProcess(&readyQueue);
			currentProcess->Start(currentTime);
		}
		
		currentTime++;
		updateWaitingTime(readyQueue);
	} while (!readyQueue.empty() || currentProcess != nullptr);

	printProcessList(processes);
}

void shortestJobFirst(const std::vector<Process> processList)
{
	auto numOfContextSwitch = 0;
	auto currentTime = 0;
	std::vector<Process*> processes;
	std::vector<Process*> readyQueue;

	Process* currentProcess = nullptr;

	for (auto process : processList)
	{
		processes.push_back(new Process(process.ProcessID, process.ArrivalTime, process.CPUBurst));
	}

	do
	{
		updateArrivalTime(processes, &readyQueue);

		if (currentProcess != nullptr)
		{
			currentProcess = currentProcess->Use(currentTime);
		}

		if (!readyQueue.empty())
		{
			std::ranges::sort(readyQueue,
				[](Process* a, Process* b) -> bool
				{
					return a->CPUBurst < b->CPUBurst;
				});

			if (currentProcess != nullptr)
			{
				if (currentProcess->CPUBurst > readyQueue.front()->CPUBurst)
				{
					readyQueue.push_back(currentProcess);
					currentProcess = changeProcess(&readyQueue);
					numOfContextSwitch++;
				}
			}
			else
			{
				currentProcess = changeProcess(&readyQueue);
				numOfContextSwitch++;
			}

			currentProcess->Start(currentTime);
		}
		
		currentTime++;
		updateWaitingTime(readyQueue);
	} while (!readyQueue.empty() || currentProcess != nullptr);

	printProcessList(processes);
	Utils::ConsoleLog::Info("Num of Context Switching: {0}", numOfContextSwitch);
}

void roundRobin(const std::vector<Process> processList, int maxTimeSlice)
{
	auto currentTimeSlice = 0;
	auto currentTime = 0;
	
	std::vector<Process*> processes;
	std::vector<Process*> readyQueue;

	Process* currentProcess = nullptr;

	for (auto process : processList)
	{
		processes.push_back(new Process(process.ProcessID, process.ArrivalTime, process.CPUBurst));
	}

	do
	{
		updateArrivalTime(processes, &readyQueue);

		if (currentProcess != nullptr)
		{
			currentProcess = currentProcess->Use(currentTime);
			currentTimeSlice++;

			if (currentProcess == nullptr)
			{
				if (!readyQueue.empty())
				{
					currentProcess = changeProcess(&readyQueue);
					currentProcess->Start(currentTime);
				}
				
				currentTimeSlice = 0;
			}

			if (currentTimeSlice == maxTimeSlice)
			{
				if (currentProcess != nullptr)
				{
					readyQueue.push_back(currentProcess);
				}

				if (!readyQueue.empty())
				{
					currentProcess = changeProcess(&readyQueue);
					currentProcess->Start(currentTime);
				}
				
				currentTimeSlice = 0;
			}
		}

		if (currentProcess == nullptr && !readyQueue.empty())
		{
			currentProcess = changeProcess(&readyQueue);
			currentProcess->Start(currentTime);
		}

		currentTime++;
		

		updateWaitingTime(readyQueue);
	} while (!readyQueue.empty() || currentProcess != nullptr);

	printProcessList(processes);
}

void longestJobFirst(const std::vector<Process> processList)
{
	auto numOfContextSwitch = 0;
	auto currentTime = 0;
	std::vector<Process*> processes;
	std::vector<Process*> readyQueue;

	Process* currentProcess = nullptr;

	for (auto process : processList)
	{
		processes.push_back(new Process(process.ProcessID, process.ArrivalTime, process.CPUBurst));
	}

	do
	{
		updateArrivalTime(processes, &readyQueue);

		if (currentProcess != nullptr)
		{
			currentProcess = currentProcess->Use(currentTime);
		}

		if (!readyQueue.empty())
		{
			std::ranges::sort(readyQueue,
                [](Process* a, Process* b) -> bool
                {
                    return a->CPUBurst > b->CPUBurst;
                });

			if (currentProcess != nullptr)
			{
				if (currentProcess->CPUBurst < readyQueue.front()->CPUBurst)
				{
					readyQueue.push_back(currentProcess);
					currentProcess = changeProcess(&readyQueue);
					numOfContextSwitch++;
				}
			}
			else
			{
				currentProcess = changeProcess(&readyQueue);
				numOfContextSwitch++;
			}

			currentProcess->Start(currentTime);
		}
		
		currentTime++;
		updateWaitingTime(readyQueue);
	} while (!readyQueue.empty() || currentProcess != nullptr);

	printProcessList(processes);
	Utils::ConsoleLog::Info("Num of Context Switching: {0}", numOfContextSwitch);
}

auto main(int argc, char** argv) -> int
{
	Utils::ConsoleLog::Init();
	
	const auto given = std::vector<Process>
	{
		Process("P1", 0, 7),
		Process("P2", 1, 11),
		Process("P3", 2, 6),
		Process("P4", 3, 5),
		Process("P5", 4, 5),
		Process("P6", 6, 2),
		Process("P7", 7, 3),
		Process("P8", 8, 6),
		Process("P9", 9, 3),
		Process("P10", 10, 3)
	};

	const auto given2 = std::vector<Process>
	{
		Process("P1", 2, 6),
	    Process("P2", 5, 2),
		Process("P3", 1, 8),
        Process("P4", 0, 3),
		Process("P5", 4, 4),
	};

	const auto given3 = std::vector<Process>
	{
		Process("P1", 0, 4),
	    Process("P2", 1, 5),
	    Process("P3", 2, 2),
		Process("P4", 3, 1),
		Process("P5", 4, 6),
		Process("P6", 6, 3),
	};

	const auto ascendingProcess = std::vector<Process>
	{
		Process("P1", 0, 20),
	    Process("P2", 0, 21),
	    Process("P3", 0, 22),
	    Process("P4", 0, 23),
	    Process("P5", 0, 24),
	    Process("P6", 0, 25),
	};

	const auto decendingProcess = std::vector<Process>
	{
		Process("P1", 0, 25),
	    Process("P2", 0, 24),
	    Process("P3", 0, 23),
	    Process("P4", 0, 22),
	    Process("P5", 0, 21),
	    Process("P6", 0, 20),
	};

	const auto equalProcess = std::vector<Process>
	{
		Process("P1", 0, 25),
	    Process("P2", 0, 25),
	    Process("P3", 0, 25),
	    Process("P4", 0, 25),
	    Process("P5", 0, 25),
	    Process("P6", 0, 25),
	};

	// firstComeFirstServe(given);
	// shortestJobFirst(given);
	// roundRobin(given, 5);
	Utils::ConsoleLog::Info("Shortest Job First");
	shortestJobFirst(ascendingProcess);
	std::cout << "\n";
	shortestJobFirst(decendingProcess);
	std::cout << "\n";
	shortestJobFirst(equalProcess);
	
	std::cout << "\n";
	std::cout << "\n";
	
	Utils::ConsoleLog::Info("Longest Job First");
	longestJobFirst(ascendingProcess);
	std::cout << "\n";
	longestJobFirst(decendingProcess);
	std::cout << "\n";
	longestJobFirst(equalProcess);
}
