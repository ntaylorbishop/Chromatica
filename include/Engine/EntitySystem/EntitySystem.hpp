#pragma once

#define IS_JOB_SYSTEM_WORKING false

#include "Engine/General/Core/BuildConfig.hpp"
#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Core/Structures/LocklessQueue.hpp"
#include "Engine/EntitySystem/ApparatusEntity.hpp"
#include "Engine/General/JobSystem/JobSystem.hpp"

class EntitySystem {
public:
	static void Initialize();
	static void Destroy();

	static void RegisterEntity(ApparatusEntity* aEntity);
	static void UnregisterEntity(ApparatusEntity* aEntity);

	static ApparatusEntity** GetActiveEntities() { return s_theEntitySystem->m_entities; }

private:
	EntitySystem();
	~EntitySystem();

	void InternalRegisterEntity(ApparatusEntity* aEntity);
	void InternalUnregisterEntity(ApparatusEntity* aEntity);

	void Update(float deltaSeconds);
	static void UpdateEntitiesJob(Job* job);
	void CleanDeadEntities();

	ApparatusEntity* m_entities[MAX_NUM_ENTITIES];
	uint m_entityCount;

	static EntitySystem* s_theEntitySystem;
};