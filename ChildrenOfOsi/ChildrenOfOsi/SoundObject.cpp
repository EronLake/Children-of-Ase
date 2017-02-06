#include "SoundObject.h"

SoundObject::SoundObject(const char* name, FMOD::Sound **sound, foo::soundType type)
	: name(name),
	ispaused(false),
	sound(*sound)
{
	// allocate channel based on soundtype and availabel channels
	// initialize time length off sound

};
const char* SoundObject::getName() {
	return name;

};
FMOD::Sound* SoundObject::getSound() {
	return sound;

};
FMOD::Channel* SoundObject::getChannel(){
	return channel;
};

