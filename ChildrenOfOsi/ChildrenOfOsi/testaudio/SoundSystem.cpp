using namespace std;
#include <iostream>
#include "fmod.hpp"
#include "fmod_errors.h" // Only if you want error checking
#include "SoundSystem.h"
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

	void SoundSystemClass::playSound(SoundClass pSound, bool bLoop )
	{
		if (!bLoop)
			pSound->setMode(FMOD_LOOP_OFF);
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL);
			pSound->setLoopCount(-1);
		}

		result = m_pSystem->playSound(pSound,0, false, 0); //fmod playsound takes  (FMOD::Sound *sound,FMOD::ChannelGroup *channelgroup, bool paused, FMOD::Channel **channel)
		cout << FMOD_ErrorString(result) << endl;
	};
	
	void SoundSystemClass::releaseSound(SoundClass pSound)
	{
		pSound->release();
	};
	void SoundSystemClass::playSoundObject(SoundObject sound)
	{
		FMOD::Sound* soundSample = sound.getSound();
		SoundSystemClass::createSound(&soundSample, sound.getName());
		bool bLoop = false;
		SoundSystemClass::playSound(sound.getSound(), bLoop);
		if (bLoop == false){
			// then wait until over and remove
			SoundSystemClass::releaseSound(sound.getSound());
		}
		

	};
	void SoundSystemClass::changeSoundSource(SoundObject sound, const char* name)
	{
		// switch the address of the sound being played.
	};
	
