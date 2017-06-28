#pragma once
#include "stdafx.h"
#include "SoundObject.h"
#include <map>
#include <vector>
#include "RegionState.h"
typedef FMOD::Sound* SoundClass;

class SoundSystem {
public:
	SoundSystem();
	~SoundSystem();

	//void Update();

    FMOD::System *m_pSystem;

	int nextChannelId;
	int driverCount;
	FMOD::Channel* chnls[36];
	
	typedef std::map<std::string, SoundClass> soundMap;
	typedef std::map<std::string, FMOD::Channel**> channelMap;
	//typedef map<int, FMOD::Channel*> channelMap;
	soundMap sounds;
	soundMap addresses;
	channelMap channels;
//	channelMap channels;

	void createMusic(SoundClass* const & pSound, string pFile);
	void createSound(SoundClass* const & pSound, std::string pFile);
	void playSound(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused,float volume);
	void playMusic(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused, float volume, RegionState::soundType type);
	void playInitialMusic(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused, float volume, RegionState::soundType type);
	void playAmbient(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused, float volume);
	void releaseSound(SoundClass pSound);
	int SoundSystem::pauseSound(std::string name);
	int SoundSystem::unpauseSound(std::string name);
	int SoundSystem::stopSound(std::string name);
	//void playSoundObject(SoundObject sound);
	int changeSoundSource(char* from, char* to, RegionState::soundType type);

	int playSong(std::string name, RegionState::soundType type);
	int playSound(std::string name, RegionState::soundType type);

	//sounds sounds_map;
	
	
	

};