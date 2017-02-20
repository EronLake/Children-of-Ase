#pragma once
#include "stdafx.h"
#include "SoundObject.h"
#include <map>
#include <vector>
typedef FMOD::Sound* SoundClass;

class SoundSystem {
public:
	SoundSystem();
	~SoundSystem();

	//void Update();

    FMOD::System *m_pSystem;

	int nextChannelId;
	int driverCount;
	
	typedef std::map<std::string, SoundClass> soundMap;
	//typedef map<int, FMOD::Channel*> channelMap;
	soundMap sounds;
//	channelMap channels;

	void createSound(SoundClass *pSound, std::string pFile);
	void playSound(SoundClass pSound, bool bLoop, FMOD::Channel* channel, bool ispaused,float volume);
	void playMusic(SoundClass pSound, bool bLoop, FMOD::Channel* channel, bool ispaused, float volume);
	void releaseSound(SoundClass pSound);
	//void playSoundObject(SoundObject sound);
	//void changeSoundSource(SoundObject sound, const char* name);
	FMOD::Channel *channels[32];
	int playSong1();
	int playBump();
	int playWalk();
	//sounds sounds_map;
	
	
	

};