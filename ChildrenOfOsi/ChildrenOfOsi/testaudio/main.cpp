using namespace std;


#include <cstdio>
#include <iostream>
#include "fmod.hpp"
#include "SoundSystem.h"
#include "SoundObject.h"
#include "soundType.h"

typedef FMOD::Sound* SoundClass;
int main()
{
	FMOD::Channel *channels[32];
	foo::soundType type;
	type = foo::soundType::music;
	// Initialize our sound system
	SoundSystemClass soundsystem;
	
	FMOD::Sound* soundSample;

	SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
	// Create a sample sound
	
	soundsystem.createSound(&soundSample, playable->getName());
	//(tried to do &playable->getsound() but that doesnt work)
	 

	// Play the sound, with loop mode
	
	soundsystem.playSound(playable->getSound(), false);

	// Do something meanwhile...
	cout << "Press return to quit." << endl;
	cin.get();

	// Release the sound
	
	
	

	soundsystem.releaseSound(soundSample);
}
