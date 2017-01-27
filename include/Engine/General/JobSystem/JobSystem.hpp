#pragma once

#include "stdint.h"
#include "Engine/General/Core/Allocators/ObjectPool.hpp"
#include "Engine/General/Core/Structures/LocklessQueue.hpp"
#include "Engine/General/JobSystem/Job.hpp"
#include "Engine/General/Core/Structures/Thread.hpp"
#include "Engine/General/JobSystem/JobConsumer.hpp"

const uint MAX_NUM_THREADS = 64;
const uint MAX_NUM_CATEGORIES = 1000;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTS
//---------------------------------------------------------------------------------------------------------------------------
struct JobThread {
	Thread m_thread;
	JobThread* m_next;
};

//---------------------------------------------------------------------------------------------------------------------------
//JOB SYSTEM CLASS
//---------------------------------------------------------------------------------------------------------------------------
class JobSystem {
public:
	static void Startup(uint numCategories, int numThreads);
	static void Shutdown();

	static bool IsJobSystemRunning() { return (s_theJobSystem->m_isActive); }

	static void WaitForJobs(const std::vector<Job*> jobs);
	static void AddWorker(uint numCategories, va_list categories );
	static Job* CreateJob(uint16_t category, JobFunctionPtr* jobWorkFunc);

private:
	//STRUCTORS INIT
	JobSystem(uint numCategories, int numThreads);
	~JobSystem();
	void Initialize();
	void InitializeJobThreadList();
	static void WorkerJobThread(void* userData);

	//INTERNALS
	LocklessQueue<Job*>* GetQueueForCategory(uint16_t category);
	void PushJobConsumerToList(JobConsumer* consumer);

	static void DispatchJobToAppropriateQueue(Job* job);

	uint m_numThreads;
	uint m_numCategories;
	ObjectPool<Job> m_jobPool;

	JobThread* m_jobThreadList;
	int m_prioritySwitch[MAX_NUM_THREADS];

	LocklessQueue<Job*>* m_jobQueues[MAX_NUM_CATEGORIES];

	JobConsumer* m_jobConsumers[MAX_NUM_CATEGORIES];
	uint m_numConsumers;

	bool m_hasStarted;
	bool m_isActive;

	static JobSystem* s_theJobSystem;

	friend class JobConsumer;
	friend class Job;
};

uint SystemGetCoreCount();