#pragma once

#include "Engine/Math/Vector2.hpp"
#include "Game/Entity.hpp"

class GameParticle : public Entity {
public:
	GameParticle(const Vector2& pos, const Vector2& vel, const String& name);

	void Update(float deltaSeconds);

	VIRTUAL void Kill(bool playDeathEffect = true);

	//TYPE DEFS
	virtual bool IsParticle() const { return true; }

	bool m_isFading;

private:
	Vector2 m_velocity;

	//INHERITED
	//Vector2 m_position;
	//float m_rotation;
	//Sprite* m_sprite;
};