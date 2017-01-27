#pragma once

#include "Engine/General/Core/Structures/LocklessQueue.hpp"
#include "Engine/General/JobSystem/Job.hpp"

const uint MAX_NUM_CONSUMER_CATEGORIES = 100;

class JobConsumer {
public:
	//STRUCTORS
	JobConsumer();
	JobConsumer(uint numCategories, ... );

	//CONSUMPTION
	void ConsumeAll();
	bool Consume();

private:
	void PushToList(LocklessQueue<Job*>* jobQueue);

	LocklessQueue<Job*>* m_queueList[MAX_NUM_CONSUMER_CATEGORIES];
	uint m_numQueues;
};