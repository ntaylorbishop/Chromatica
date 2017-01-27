/*
#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include <functional>

//---------------------------------------------------------------------------------------------------------------------------
//APPARATUS ENTITY CREATION DATA
//---------------------------------------------------------------------------------------------------------------------------
class ApparatusEntityData {
public:
	//STRUCTORS
	ApparatusEntityData();
	ApparatusEntityData(const String& entityName);

	//GETTERS SETTERS
	String GetEntityName() const { return m_entityName; }

protected:
	String m_entityName;
};

typedef ApparatusEntityData* (EntityCreationFunc)(const String& name);


//---------------------------------------------------------------------------------------------------------------------------
//ENTITY DATA REGISTRATION
//---------------------------------------------------------------------------------------------------------------------------
class ApparatusEntityDataRegistration {
public:
	ApparatusEntityDataRegistration(const String& name, EntityCreationFunc* creationFunc);
	static ApparatusEntityData* CreateEntityDataByName(const String& name);

	static std::map<size_t, ApparatusEntityDataRegistration*>* ApparatusEntityDataRegistration::s_entityDataRegistrationMap;

private:
	String m_name;
	EntityCreationFunc* m_creationFunc;


	friend class EntitySystem;
};*/