#include "stdafx.h"
#include "common.h"
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
	//FMOD::System *m_pSystem;

	SoundSystem::SoundSystem()
	{
		if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
		{
			// Report Error
			return;
		}


		driverCount = 0;
		m_pSystem->getNumDrivers(&driverCount);

		if (driverCount == 0)
		{
			// Report Error
			return;
		}
		
		// Initialize our Instance with 36 Channels
		m_pSystem->init(36, FMOD_INIT_NORMAL, 0);
		string oasis = "Music/RegionThemes/DesertRegion.flac";
		string jungle = "Music/RegionThemes/JungleRegion.flac";
		string mountain = "Music/RegionThemes/MountainRegion.flac";
		string marsh = "Music/RegionThemes/MarshRegion.flac";
		string ogun = "Music/HeroThemes/ogun.flac";
		string oya = "Music/HeroThemes/oya.flac";

		string bump = "SFX/bump_0.wav";
		string walk = "SFX/walk_loop.wav";
		string swing = "SFX/swing.wav";
		string hit = "SFX/hit.wav";
		string up = "SFX/up.wav";
		string down = "SFX/down.wav";
		string page = "SFX/page.wav";
		string talk = "SFX/talk.wav";




		SoundClass oasisAddress = nullptr;
		SoundClass jungleAddress = nullptr;
		SoundClass mountainAddress = nullptr;
		SoundClass marshAddress = nullptr;
		SoundClass ogunAddress = nullptr;
		SoundClass oyaAddress = nullptr;

		SoundClass bumpAddress = nullptr;
		SoundClass walkAddress = nullptr;
		SoundClass swingAddress = nullptr;
		SoundClass hitAddress = nullptr;
		SoundClass upAddress = nullptr;
		SoundClass downAddress = nullptr;
		SoundClass pageAddress = nullptr;
		SoundClass talkAddress = nullptr;


		this->createSound(&oasisAddress, oasis);
		this->createSound(&jungleAddress, jungle);
		this->createSound(&mountainAddress, mountain);
		this->createSound(&marshAddress, marsh);
		this->createSound(&ogunAddress, ogun);
		this->createSound(&oyaAddress, oya);

		this->createSound(&bumpAddress, bump);
		this->createSound(&walkAddress, walk);
		this->createSound(&swingAddress, swing);
		this->createSound(&hitAddress, hit);
		this->createSound(&upAddress, up);
		this->createSound(&downAddress, down);
		this->createSound(&pageAddress, page);
		this->createSound(&talkAddress, talk);

		sounds[oasis] = oasisAddress;
		sounds[jungle] = jungleAddress;
		sounds[mountain] = mountainAddress;
		sounds[marsh] = marshAddress;
		sounds[ogun] = ogunAddress;
		sounds[oya] = oyaAddress;

		sounds[bump] = bumpAddress;
		sounds[walk] = walkAddress;
		sounds[swing] = swingAddress;
		sounds[hit] = hitAddress;
		sounds[up] = upAddress;
		sounds[down] = downAddress;
		sounds[page] = pageAddress;
		sounds[talk] = talkAddress;
	}

	SoundSystem::~SoundSystem() {
		LOG("SoundSystem Destructed");
	}

	void SoundSystem::createSound(SoundClass *pSound, string pFile)
	{
		auto sound = sounds.find(pFile);
		if (sound != sounds.end()) return; //Sound already loaded

		result = m_pSystem->createSound(pFile.c_str(), FMOD_DEFAULT, 0, pSound);//fmod createSound takes (const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD::Sound **sound)
		//////cout << FMOD_ErrorString(result) << endl;

		if (pSound) {
			sounds[pFile] = *pSound;
		}
	}

	void SoundSystem::playSound(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused , float volume)
	{
		if (!bLoop)
			pSound->setMode(FMOD_LOOP_OFF);
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL);
			pSound->setLoopCount(-1);
		}


		result = m_pSystem->playSound(pSound,0, ispaused, &channel); //fmod playsound takes  (FMOD::Sound *sound,FMOD::ChannelGroup *channelgroup, bool paused, FMOD::Channel **channel)
		channel->setVolume(volume);
		
		channel->setPaused(false);
		channel->setPriority(255);
		if (bLoop){
		channel->setLoopCount(-1);
		}
		//////cout << FMOD_ErrorString(result) << endl;
	};
	void SoundSystem::playMusic(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused, float volume, RegionState::soundType type)
	{
		if (!bLoop)
			pSound->setMode(FMOD_LOOP_OFF);
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL);
			pSound->setLoopCount(-1);
		}
			
	

		result = m_pSystem->playSound(pSound, 0, ispaused, &channel); //fmod playsound takes  (FMOD::Sound *sound,FMOD::ChannelGroup *channelgroup, bool paused, FMOD::Channel **channel)
		channel->setVolume(volume);
		unsigned long long dspclock;
		int rate;
		result = channel->getSystemObject(&m_pSystem);                        // OPTIONAL : Get System object
		result = m_pSystem->getSoftwareFormat(&rate, 0, 0);                // Get mixer rate
		result = channel->getDSPClock(0, &dspclock);
		if (type == RegionState::soundType::region_music) {
			                  // Get the reference clock, which is the parent channel group   
			// Add a fade point at 'now' with full volume.
			result = channel->setDelay(dspclock + (rate * 3), 0, false);
			result = channel->addFadePoint(dspclock + (rate * 3), 0.0f);
			result = channel->addFadePoint(dspclock + (rate * 6), volume); // Add a fade point 5 seconds later at 0 volume.
		}

		channel->setPaused(false);
		channel->setPriority(0);
		if (bLoop) {
			channel->setLoopCount(-1);
		}
		//////cout << FMOD_ErrorString(result) << endl;
	};
	void SoundSystem::playAmbient(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused, float volume)
	{
		if (!bLoop)
			pSound->setMode(FMOD_LOOP_OFF);
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL);
			pSound->setLoopCount(-1);
		}



		result = m_pSystem->playSound(pSound, 0, ispaused, &channel); //fmod playsound takes  (FMOD::Sound *sound,FMOD::ChannelGroup *channelgroup, bool paused, FMOD::Channel **channel)
		channel->setVolume(volume);
		channel->setPaused(false);
		channel->setPriority(1);
		if (bLoop) {
			channel->setLoopCount(-1);
		}
		//////cout << FMOD_ErrorString(result) << endl;
	};
	void SoundSystem::releaseSound(SoundClass pSound)
	{
		pSound->release();
	};

	
	int SoundSystem::playSong(std::string name, RegionState::soundType type) {

		chnls[0] = nullptr;
		bool ispaused = true;
		unsigned int time;
		if (type == RegionState::soundType::region_music) {
			channels[name.c_str()] = &chnls[0];//assign the channel
			playMusic(sounds[name], true, chnls[0], ispaused, .9,type);
		}
		else if (type == RegionState::soundType::theme_music) {
			channels[name.c_str()] = &chnls[0];//assign the channel
			playMusic(sounds[name], true, chnls[0], ispaused, .7,type);
		}
		else
			return 1;
		return 0;// Release the sound
	}
	int SoundSystem::playSound(std::string name, RegionState::soundType type) {
		int channel = rand() %27 +5;
		chnls[channel] = nullptr;
		bool ispaused = true;
		unsigned int time;
		if (type == RegionState::soundType::sfx) {
			channels[name.c_str()] = &chnls[channel];//assign the channel
			playSound(sounds[name], false, chnls[channel], ispaused, .5);
		}
		else if (type == RegionState::soundType::ambient_sfx) {
			channels[name.c_str()] = &chnls[channel];//assign the channel
			playAmbient(sounds[name], false, chnls[channel], ispaused, .5);
		}
		else
			return 1;
		return 0;// Release the sound
	}
	
	
	int SoundSystem::pauseSound(string name) {
	            //the variables required

		FMOD::Channel* channel;
		if ((channels[name])) {
			channel = *(channels[name]);
			bool playing = false;
			bool* isplaying = &playing;
			channel->isPlaying(isplaying);
			if (*isplaying) {
				channel->setPaused(true);
			}

		}
		
																////////cout << "Press return to quit." << endl;  // Do something meanwhile...
																//cin.get();

																//releaseSound(sounds[name]); 
		return 0;// Release the sound 
	};
	int SoundSystem::unpauseSound(string name)
	{
		FMOD::Channel* channel;
		if ((channels[name])) {
			channel = *(channels[name]);
			bool playing = true;
			bool* isplaying = &playing;
			channel->isPlaying(isplaying);
			if (*isplaying) {
				channel->setPaused(false);
			}
		}
		return 0;
	};
	
	int SoundSystem::changeSoundSource(char* from, char* to, RegionState::soundType type)
	{
		if (from == nullptr) {
			playSong(to, type);
			return 0;
		}
		if (type == RegionState::soundType::region_music) {
			int t = stopSound(from);
			if (t ==  0) {
				playSong(to, type);
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else if (type == RegionState::soundType::theme_music) {

			FMOD::Channel* channel;
			string name = from;
			if ((channels[from])) {
				channel = *(channels[from]);
				bool playing = false;
				bool* isplaying = &playing;
				channel->isPlaying(isplaying);
				if (*isplaying) {
					channel->stop();
					playSong(to, type);


					//then play new sound
				}
				else
					return 1;
			}
			else
				return 1;
		}
		else
			return 1;
		
	
	};
	int SoundSystem::stopSound(string name)
	{
		FMOD::Channel* channel;
		if ((channels[name.c_str()])) {
			channel = *(channels[name.c_str()]);
			bool playing = true;
			bool* isplaying = &playing;
			channel->isPlaying(isplaying);
			if (*isplaying) {
				unsigned long long dspclock;
				int rate;
				result = channel->getSystemObject(&m_pSystem);                        // OPTIONAL : Get System object
				result = m_pSystem->getSoftwareFormat(&rate, 0, 0);                // Get mixer rate
				result = channel->getDSPClock(0, &dspclock);                    // Get the reference clock, which is the parent channel group
				result = channel->addFadePoint(dspclock, 1.0f);                 // Add a fade point at 'now' with full volume.
				result = channel->addFadePoint(dspclock + (rate * 3), 0.0f);    // Add a fade point 5 seconds later at 0 volume.
				result = channel->setDelay(0, dspclock + (rate * 3), true);
				return 0;
			}
			else
				return 1;
		}
		else
			return 1;
		
	};
	
