#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Time/Clock.hpp"

class TheStarryBackground {
public:
	static void Initialize();
	static void Destroy();

private:
	TheStarryBackground();
	~TheStarryBackground();

	void Update(float deltaSeconds);
	void SpawnStar();

	Clock m_clock;
	Vector2 m_systemVelocity;
	float m_age;

	static TheStarryBackground* s_theStarryBackground;
};