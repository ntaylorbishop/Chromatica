#pragma once

#include "Engine/Math/RangeFloat.hpp"
#include "Engine/Renderer/SpriteRenderer/SpriteResource.hpp"
#include "Engine/Renderer/SpriteRenderer/ParticleSystem/Particle.hpp"
#include "Engine/Renderer/SpriteRenderer/ParticleSystem/ParticleEmitterDefinition.hpp"

class ParticleSystemDefinition {
public:

	static ParticleSystemDefinition* RegisterParticleSystemDefinition(const String& name);
	static ParticleSystemDefinition* Get(const String& name);
	ParticleEmitterDefinition* AddEmitter(ParticleEmitterDefinition* emitterDef);

	static void DeinitializeAllDefinitions();

	bool IsLooping();

private:
	ParticleSystemDefinition(const String& name);

	Clock m_clock;
	String m_name;
	bool m_isLooping;
	bool m_hasCheckedForLooping;
	std::vector<ParticleEmitterDefinition*> m_emitterDefs;

	friend class ParticleSystem;


	static std::map<size_t, ParticleSystemDefinition*, std::less<size_t>, UntrackedAllocator<std::pair<size_t, ParticleSystemDefinition*>>> s_registeredParticleSystemDefs;
};

typedef std::map<size_t, ParticleSystemDefinition*, std::less<size_t>, UntrackedAllocator<std::pair<size_t, ParticleSystemDefinition*>>> ParticleSystemDefinitionMap;
typedef std::map<size_t, ParticleSystemDefinition*, std::less<size_t>, UntrackedAllocator<std::pair<size_t, ParticleSystemDefinition*>>>::iterator ParticleSystemDefinitionMapIterator;
typedef std::pair<size_t, ParticleSystemDefinition*> ParticleSystemDefinitionMapPair;