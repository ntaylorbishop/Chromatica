#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Time/Clock.hpp"
#include "Engine/Renderer/SpriteRenderer/ParticleSystem/ParticleEmitter.hpp"
#include "Engine/Renderer/SpriteRenderer/ParticleSystem/ParticleSystemDefinition.hpp"


class ParticleSystem {
public:
	static ParticleSystem* Spawn(const String& name, const String& layerName, const Vector2& pos);
	static ParticleSystem* Play(const String& systemName, const String& layerName, const Vector2& pos);
	static ParticleSystem* Stop(ParticleSystem* system);

	bool IsPlaying() const { return m_isPlaying; }

private:
	ParticleSystem(const String& name, const String& layerName, const Vector2& pos);
	~ParticleSystem();

	void Update(float deltaSeconds);

	String m_name;
	String m_layerID;
	Clock m_clock;
	bool m_isPlaying;
	Vector2 m_pos;
	ParticleSystemDefinition* m_systemDef;
	std::vector<ParticleEmitter*> m_emitters;

	ParticleSystem* m_next;
	ParticleSystem* m_prev;

	friend class SpriteLayer;
};