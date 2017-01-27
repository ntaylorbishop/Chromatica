#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/EntitySystem/ApparatusEntityData.hpp"

class ApparatusEntity {
public:
	ApparatusEntity();
	virtual ~ApparatusEntity();

	virtual void Update(float deltaSeconds) = 0;

	bool operator==(const ApparatusEntity& other);
	bool operator!=(const ApparatusEntity& other);

	bool m_isAlive;

protected:
	uint m_id;

private:
	ApparatusEntity* m_next;
	ApparatusEntity* m_prev;

	static uint s_aEntityId;
};

inline bool ApparatusEntity::operator==(const ApparatusEntity& other) {
	return (m_id == other.m_id);
}
inline bool ApparatusEntity::operator!=(const ApparatusEntity& other) {
	return (m_id != other.m_id);
}

/*
//---------------------------------------------------------------------------------------------------------------------------
//REGISTRATION
//---------------------------------------------------------------------------------------------------------------------------

typedef ApparatusEntity* (AEntityCreationFunc)(ApparatusEntityData* genData);

class AEntityRegistration {
public:
	AEntityRegistration(const String& name, AEntityCreationFunc* creationFunc);
	static ApparatusEntity* CreateEntityByName(const String& name, ApparatusEntityData* aEntityData);

	static std::map<size_t, AEntityRegistration*>* AEntityRegistration::s_aEntityRegistrationMap;


public:
	String m_name;
	AEntityCreationFunc* m_creationFunc;


	friend class EntitySystem;
};*/