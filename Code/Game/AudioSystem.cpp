#include "Game/AudioSystem.hpp"
#include "Engine/General/Core/GameEngine.hpp"
#include "Game/GameCommon.hpp"

STATIC AudioSystem* AudioSystem::s_audioSystem = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------------------------------
//STATICS
//---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
STATIC void AudioSystem::Initialize() {

	ASSERT_OR_DIE(s_audioSystem == nullptr, "ERROR: Tried to initialize Audio System when it already existed.");
	s_audioSystem = new AudioSystem();

	g_theApparatusEngine->RegisterUpdateCallback(MakeDelegate(s_audioSystem, &AudioSystem::Update));
}
STATIC void AudioSystem::Destroy() {

	ASSERT_OR_DIE(s_audioSystem != nullptr, "ERROR: Tried to destroy Audio System when it already existed.");
	delete s_audioSystem;
	s_audioSystem = nullptr;
}
STATIC void AudioSystem::PlayFire() {
	#if IS_SOUND_ENABLED
	s_audioSystem->InternalPlayFire();
	#endif
}
STATIC void AudioSystem::PlayHit() {
	#if IS_SOUND_ENABLED
		s_audioSystem->InternalPlayHit();
	#endif
}

STATIC void AudioSystem::PlayEndGameMusic() {
	#if IS_SOUND_ENABLED
		s_audioSystem->InternalPlayEndGameMusic();
	#endif
}
STATIC void AudioSystem::PlayGameMusicLoop() {
	#if IS_SOUND_ENABLED
		s_audioSystem->InternalPlayGameMusicLoop();
	#endif
}
STATIC void AudioSystem::PlayGameIntroLoop() {
	#if IS_SOUND_ENABLED
		s_audioSystem->InternalPlayGameIntroLoop();
	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------------------------------
//MEMBERS
//---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AudioSystem::AudioSystem() {
	m_musicTrack1ID = m_engineAudioSystem.CreateOrGetSound(MUSIC_TRACK1);
	m_musicTrack2ID = m_engineAudioSystem.CreateOrGetSound(MUSIC_TRACK2);
	m_bulletFireID = m_engineAudioSystem.CreateOrGetSound(BULLET_FIRE);
	m_bulletHitID = m_engineAudioSystem.CreateOrGetSound(BULLET_HIT);
	m_endGameMusicID = m_engineAudioSystem.CreateOrGetSound(ENDGAME_MUSIC);
}
AudioSystem::~AudioSystem() {

}

void AudioSystem::Update(float deltaSeconds) {
	m_engineAudioSystem.Update(deltaSeconds);
}

void AudioSystem::InternalPlayFire() {
	m_soundFxChannel = m_engineAudioSystem.Play(m_bulletFireID, 0.7f);
}
void AudioSystem::InternalPlayHit() {
	m_soundFxChannel = m_engineAudioSystem.Play(m_bulletHitID, 0.7f);
}
void AudioSystem::InternalPlayMusic() {
	m_musicChannel = m_engineAudioSystem.PlayLoop(m_musicTrack2ID, 1.f);
}
void AudioSystem::InternalPlayEndGameMusic() {
	m_engineAudioSystem.StopChannel(m_musicChannel);
	m_musicChannel = m_engineAudioSystem.PlayLoop(m_endGameMusicID, 1.f);
}
void AudioSystem::InternalPlayGameMusicLoop() {
	m_engineAudioSystem.StopChannel(m_musicChannel);
	m_musicChannel = m_engineAudioSystem.PlayLoop(m_musicTrack2ID, 1.f);
}
void AudioSystem::InternalPlayGameIntroLoop() {
	m_engineAudioSystem.StopChannel(m_musicChannel);
	m_musicChannel = m_engineAudioSystem.PlayLoop(m_musicTrack1ID, 1.f);
}