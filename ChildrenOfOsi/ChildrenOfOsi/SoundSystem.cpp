#include "stdafx.h"
using namespace std;
#include <iostream>
#include "fmod.hpp"
#include "fmod_errors.h" // Only if you want error checking
#include "SoundSystem.h"
#include <map>
#include <string>
typedef FMOD::Sound* SoundClass;
FMOD_RESULT result;

	// Pointer to the FMOD instance
	FMOD::System *m_pSystem;

	SoundSystemClass::SoundSystemClass()
	{
		if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
		{
			// Report Error
			return;
		}


		int driverCount = 0;
		m_pSystem->getNumDrivers(&driverCount);

		if (driverCount == 0)
		{
			// Report Error
			return;
		}
		
		// Initialize our Instance with 36 Channels
		m_pSystem->init(36, FMOD_INIT_NORMAL, 0);

	};

	void SoundSystemClass::createSound(SoundClass *pSound, const char* pFile)
	{
		result = m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);//fmod createSound takes (const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD::Sound **sound)

		cout << FMOD_ErrorString(result) << endl;
	};

	void SoundSystemClass::playSound(SoundClass pSound, bool bLoop, FMOD::Channel* channel, bool ispaused )
	{
		if (!bLoop)
			pSound->setMode(FMOD_LOOP_OFF);
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL);
			pSound->setLoopCount(-1);
		}

		result = m_pSystem->playSound(pSound,0, ispaused, &channel); //fmod playsound takes  (FMOD::Sound *sound,FMOD::ChannelGroup *channelgroup, bool paused, FMOD::Channel **channel)
		cout << FMOD_ErrorString(result) << endl;
	};
	
	void SoundSystemClass::releaseSound(SoundClass pSound)
	{
		pSound->release();
	};
	int SoundSystemClass::playSong1() {
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


		soundsystem.playSound(soundSample, false, channel, ispaused); 	// Play the sound, with loop mode


		cout << "Press return to quit." << endl;  // Do something meanwhile...
		cin.get();

		soundsystem.releaseSound(soundSample); 
		return 1;// Release the sound
	};
	
	
	/*void SoundSystemClass::playSoundObject(SoundObject sound)
	{
		FMOD::Sound* soundSample = sound.getSound();
		SoundSystemClass::createSound(&soundSample, sound.getName());
		bool bLoop = false;
		SoundSystemClass::playSound(sound.getSound(), bLoop);
		if (bLoop == false){
			// then wait until over and remove
			SoundSystemClass::releaseSound(sound.getSound());
		}
		

	};*/
	/*void SoundSystemClass::changeSoundSource(SoundObject sound, const char* name)
	{
		// switch the address of the sound being played.
	};*/
	