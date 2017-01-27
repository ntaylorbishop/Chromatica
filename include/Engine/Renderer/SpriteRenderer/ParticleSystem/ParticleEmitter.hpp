#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/SpriteRenderer/ParticleSystem/ParticleEmitterDefinition.hpp"

const uint MAX_NUM_EMITTER_PARTICLES = 100000;

class ParticleEmitter {
public:
	ParticleEmitter(ParticleEmitterDefinition* emitterDef, const String& layerName, const Vector2& position);
	~ParticleEmitter();

	void Update(float deltaSeconds);

	bool IsPlaying() const { return m_isPlaying; }

private:
	void SpawnParticles();
	void UpdateParticles(float deltaSeconds);
	void DestroyParticles();

	void AddParticleToArray(Particle* particle);

	ParticleEmitterDefinition* m_emitterDef;
	String m_layerName;
	bool m_isPlaying;
	uint m_currNumParticles;
	Vector2 m_position;

	float m_age;

	Particle* m_particles[MAX_NUM_EMITTER_PARTICLES];
};