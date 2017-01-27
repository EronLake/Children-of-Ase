using namespace std;


#include <cstdio>
#include <iostream>
#include "fmod.hpp"
#include "SoundSystem.h"
#include "SoundObject.h"
#include "soundType.h"
#include <time.h>

typedef FMOD::Sound* SoundClass;
int main()
{
	FMOD::Channel *channels[32]; //all of the channels

	foo::soundType type;
	FMOD::Sound* soundSample;
	const char* name;              //the variables required
	FMOD::Channel* channel;
	bool ispaused;
	unsigned int time;
	
	// Initialize our sound system
	SoundSystemClass soundsystem;
	
	type = foo::soundType::music;
	name = "04.wav";
	channel = channels[0];//assign the channel
	ispaused = false;
	
	soundsystem.createSound(&soundSample, name);// Create the sound
	soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

	//SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
	//object stuff
	
	
	soundsystem.playSound(soundSample, false,channel,ispaused); 	// Play the sound, with loop mode

	
	cout << "Press return to quit." << endl;  // Do something meanwhile...
	cin.get();

	soundsystem.releaseSound(soundSample); // Release the sound
	
	
	

	
}
