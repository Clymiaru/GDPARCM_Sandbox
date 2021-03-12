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
};

void printProcessList(const std::vector<Process*> processes)
{
	float averageWaitingTime = 0.0f;
	Utils::ConsoleLog::Info("Processes");
	for (auto process : processes)
	{
		Utils::ConsoleLog::Info("{0} | Start Time: {1} | End Time: {2} | Waiting Time: {3}", process->ProcessID, process->StartTime, process->EndTime, process->WaitingTime);
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
			currentProcess->CPUBurst--;
			if (currentProcess->CPUBurst <= 0)
			{
				currentProcess->EndTime = currentTime;
				currentProcess = nullptr;
			}
		}

		if (currentProcess == nullptr && !readyQueue.empty())
		{
			currentProcess = readyQueue.front();
			readyQueue.erase(readyQueue.begin());
			currentProcess->StartTime = currentTime;
			currentProcess->HasStarted = true;
		}
		
		currentTime++;
		updateWaitingTime(readyQueue);
	} while (!readyQueue.empty() || currentProcess != nullptr);

	printProcessList(processes);
}

void shortestJobFirst(const std::vector<Process> processList)
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
			currentProcess->CPUBurst--;
			if (currentProcess->CPUBurst <= 0)
			{
				currentProcess->EndTime = currentTime;
				currentProcess = nullptr;
			}
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
					currentProcess = readyQueue.front();
					readyQueue.erase(readyQueue.begin());

					if (!currentProcess->HasStarted)
					{
						currentProcess->StartTime = currentTime;
					}
					
				}
			}
			else
			{
				currentProcess = readyQueue.front();
				readyQueue.erase(readyQueue.begin());

				if (!currentProcess->HasStarted)
				{
					currentProcess->StartTime = currentTime;
				}
			}
		}
		
		currentTime++;
		updateWaitingTime(readyQueue);
	} while (!readyQueue.empty() || currentProcess != nullptr);

	printProcessList(processes);
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

	// firstComeFirstServe(given);
	shortestJobFirst(given);
}
