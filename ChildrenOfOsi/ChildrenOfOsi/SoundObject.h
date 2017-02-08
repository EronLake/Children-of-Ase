#ifndef SoundObjectHEADER
#define SoundObjectHEADER

#include "fmod.hpp"
#include "soundType.h"
class SoundObject {
private:
	const char* name;
	FMOD::Channel*  channel;
	FMOD::Sound* sound;
	bool ispaused;
	
public:
	SoundObject(const char* name, FMOD::Sound **sound, foo::soundType type);
	FMOD::Sound* getSound();
	const char* getName();
	FMOD::Channel* getChannel();

	
};
#endif