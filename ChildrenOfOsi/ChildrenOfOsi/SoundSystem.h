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
	FMOD::Channel *chnls[32];
	
	typedef std::map<std::string, SoundClass> soundMap;
	typedef std::map<std::string, FMOD::Channel**> channelMap;
	//typedef map<int, FMOD::Channel*> channelMap;
	soundMap sounds;
	channelMap channels;
//	channelMap channels;

	void createSound(SoundClass *pSound, std::string pFile);
	void playSound(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused,float volume);
	void playMusic(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused, float volume);
	void playAmbient(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused, float volume);
	void releaseSound(SoundClass pSound);
	int SoundSystem::pauseSound(std::string name);
	int SoundSystem::unpauseSound(std::string name);
	int SoundSystem::stopSound(std::string name);
	//void playSoundObject(SoundObject sound);
	int changeSoundSource(char* from, char* to);

	int playSong(const char* _name);
	int playSong1();
	int playSong2();
	int playBump();
	int playWalk();
	int playSixers();
	//sounds sounds_map;
	
	
	

};