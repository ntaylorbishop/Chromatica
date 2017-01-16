#pragma once

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Audio/ApparatusAudioSystem.hpp"




class AudioSystem {
public:
	static void Initialize();
	static void Destroy();

	static void PlayFire();
	static void PlayHit();
	static void PlayEndGameMusic();
	static void PlayGameMusicLoop();
	static void PlayGameIntroLoop();

private:
	AudioSystem();
	~AudioSystem();

	void InternalPlayFire();
	void InternalPlayHit();
	void InternalPlayMusic();
	void InternalPlayEndGameMusic();
	void InternalPlayGameMusicLoop();
	void InternalPlayGameIntroLoop();

	void Update(float deltaSeconds);

	ApparatusAudioSystem m_engineAudioSystem;

	AudioChannelHandle m_musicChannel;
	AudioChannelHandle m_soundFxChannel;

	static AudioSystem* s_audioSystem;

	SoundID m_endGameMusicID;
	SoundID m_musicTrack1ID;
	SoundID m_musicTrack2ID;
	SoundID m_bulletFireID;
	SoundID m_bulletHitID;

	const String MUSIC_TRACK1 = "Data/Sounds/Music1.mp3";
	const String MUSIC_TRACK2 = "Data/Sounds/Music2.mp3";
	const String ENDGAME_MUSIC = "Data/Sounds/EndGame.mp3";
	const String BULLET_FIRE = "Data/Sounds/PlayerFire.wav";
	const String BULLET_HIT = "Data/Sounds/BulletHit.wav";
};