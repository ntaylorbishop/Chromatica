#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Time/Time.hpp"
#include <vector>

class Clock {
public:
	//STRUCTORS
	Clock();
	Clock(Clock* parent);
	Clock(Clock* parent, float scale);
	~Clock();

	//UPDATE
	void Update(float deltaSeconds);

	//GETTERS
	double GetCurrent() const { return m_currentTime; }
	double GetDelta() const { return m_deltaTime; }

	void SetScale(float scale) { m_scale = scale; }
	void Reset() { m_currentTime = 0.f; }

	void Pause() { m_paused = true; }
	void Unpause() { m_paused = false; }

	bool operator==(const Clock& other);
	bool operator!=(const Clock& other);

private:
	ulong m_id;
	bool m_paused;
	double m_scale;
	double m_currentTime;
	double m_deltaTime;
	Clock* m_parent;
	std::vector<Clock*> m_children;

	void AttachChild(Clock* clock) { m_children.push_back(clock); }
	void DetachChild(Clock* clock);

	static ulong s_clockId;
};

//---------------------------------------------------------------------------------------------------------------------------
//INLINES
//---------------------------------------------------------------------------------------------------------------------------
inline bool Clock::operator==(const Clock& other) {
	return (m_id == other.m_id);
}
inline bool Clock::operator!=(const Clock& other) {
	return (m_id != other.m_id);
}