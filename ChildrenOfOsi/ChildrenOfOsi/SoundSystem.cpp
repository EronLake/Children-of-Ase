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
	}

	void SoundSystemClass::createSound(SoundClass *pSound, const char* pFile)
	{
		result = m_pSystem->createSound(pFile, FMOD_DEFAULT, 0, pSound);
		cout << FMOD_ErrorString(result) << endl;
	}

	void SoundSystemClass::playSound(SoundClass pSound, bool bLoop )
	{
		if (!bLoop)
			pSound->setMode(FMOD_LOOP_OFF);
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL);
			pSound->setLoopCount(-1);
		}

		result = m_pSystem->playSound(pSound,0, false, 0);
		cout << FMOD_ErrorString(result) << endl;
	}

	void SoundSystemClass::releaseSound(SoundClass pSound)
	{
		pSound->release();
	}
