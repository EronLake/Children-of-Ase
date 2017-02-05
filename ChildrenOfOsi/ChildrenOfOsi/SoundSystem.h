#pragma once
#include "stdafx.h"
#include "SoundObject.h"
typedef FMOD::Sound* SoundClass;
#include <vector>
class SoundSystemClass {
public:
	SoundSystemClass();
	void createSound(SoundClass *pSound, const char* pFile);
	void playSound(SoundClass pSound, bool bLoop, FMOD::Channel* channel, bool ispaused);
	void releaseSound(SoundClass pSound);
	//void playSoundObject(SoundObject sound);
	//void changeSoundSource(SoundObject sound, const char* name);
	FMOD::Channel *channels[32];
	int playSong1();
	
	
	

};