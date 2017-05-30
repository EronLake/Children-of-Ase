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

		/*string Desert = "Music/RegionThemes/DesertRegion.flac";
		string Jungle = "Music/RegionThemes/JungleRegion.flac";
		string Mountain = "Music/RegionThemes/MountainRegion.flac";
		string Marsh = "Music/RegionThemes/MarshRegion.flac";
		string Yemoja = "Music/HeroThemes/Yemoja.flac";
		string Oya = "Music/HeroThemes/Oya.flac";
		string Ogun = "Music/HeroThemes/Ogun.flac";
		string Oshosi = "Music/HeroThemes/Oshosi.flac";

		SoundClass DesertAddress = nullptr;
		SoundClass JungleAddress = nullptr;
		SoundClass MountainAddress = nullptr;
		SoundClass MarshAddress = nullptr;
		SoundClass OgunAddress = nullptr;
		SoundClass OyaAddress = nullptr;
		SoundClass YemojaAddress = nullptr;
		SoundClass OshosiAddress = nullptr;

		this->createMusic(&DesertAddress, Desert);
		this->createMusic(&JungleAddress, Jungle);
		this->createMusic(&MountainAddress, Mountain);
		this->createMusic(&MarshAddress, Marsh);
		this->createMusic(&OgunAddress, Ogun);
		this->createMusic(&OyaAddress, Oya);
		this->createMusic(&YemojaAddress, Yemoja);
		this->createMusic(&OshosiAddress, Oshosi);

		sounds[Desert] = DesertAddress;
		sounds[Jungle] = JungleAddress;
		sounds[Mountain] = MountainAddress;
		sounds[Marsh] = MarshAddress;
		sounds[Yemoja] = YemojaAddress;
		sounds[Ogun] = OgunAddress;
		sounds[Oya] = OyaAddress;
		sounds[Oshosi] = OshosiAddress;*/

		string bump = "SFX/bump_0.wav";
		string walk = "SFX/walk_0.wav";
		string swing = "SFX/swing.wav";
		string hit = "SFX/hit.wav";
		string up = "SFX/up.wav";
		string down = "SFX/down.wav";
		string page = "SFX/page.wav";
		string talk = "SFX/talk.wav";
		
		SoundClass bumpAddress = nullptr;
		SoundClass walkAddress = nullptr;
		SoundClass swingAddress = nullptr;
		SoundClass hitAddress = nullptr;
		SoundClass upAddress = nullptr;
		SoundClass downAddress = nullptr;
		SoundClass pageAddress = nullptr;
		SoundClass talkAddress = nullptr;

		this->createSound(&bumpAddress, bump);
		this->createSound(&walkAddress, walk);
		this->createSound(&swingAddress, swing);
		this->createSound(&hitAddress, hit);
		this->createSound(&upAddress, up);
		this->createSound(&downAddress, down);
		this->createSound(&pageAddress, page);
		this->createSound(&talkAddress, talk);

		

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

	void SoundSystem::createMusic(SoundClass* const & pSound, string pFile)
	{
		auto sound = sounds.find(pFile);
		if (sound != sounds.end()) {
			if (sounds[pFile] != nullptr)
				return;
		}; //Sound already loaded

		result = m_pSystem->createSound(pFile.c_str(), FMOD_CREATESTREAM|FMOD_LOWMEM, 0, pSound);//fmod createSound takes (const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD::Sound **sound)
		//////cout << FMOD_ErrorString(result) << endl;

		if (pSound) {
			sounds[pFile] = *pSound;
		}
	}
	void SoundSystem::createSound(SoundClass* const & pSound, string pFile)
	{
		auto sound = sounds.find(pFile);
		if (sound != sounds.end()) return; //Sound already loaded

		result = m_pSystem->createSound(pFile.c_str(), FMOD_DEFAULT | FMOD_LOWMEM, 0, pSound);//fmod createSound takes (const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD::Sound **sound)
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
			pSound->setMode(FMOD_LOOP_OFF| FMOD_CREATESTREAM | FMOD_LOWMEM);
		else
		{
			pSound->setMode(FMOD_LOOP_NORMAL| FMOD_CREATESTREAM | FMOD_LOWMEM);
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
		for (auto it : sounds) {
			if (it.second == pSound) {
				SoundClass new_sound = nullptr;
				sounds[it.first] = new_sound;
			}
		}
	};

	
	int SoundSystem::playSong(std::string name, RegionState::soundType type) {
		
		
		FMOD::Channel* channel = nullptr;
		chnls[0] = channel;
		bool ispaused = true;
		unsigned int time;
		if (type == RegionState::soundType::region_music) {
			channels[name.c_str()] = &chnls[0];//assign the channel
			SoundClass sound = nullptr;
			this->createMusic(&sound, name);
			playMusic(sounds[name], true, chnls[0], ispaused, 1,type);
		}
		else if (type == RegionState::soundType::theme_music) {
			channels[name.c_str()] = &chnls[0];//assign the channel
			SoundClass sound = nullptr;
			this->createMusic(&sound, name);
			playMusic(sounds[name], true, chnls[0], ispaused, .9,type);
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
			playSound(sounds[name], false, chnls[channel], ispaused, .6);
		}
		else if (type == RegionState::soundType::ambient_sfx) {
			channels[name.c_str()] = &chnls[channel];//assign the channel
			playAmbient(sounds[name], false, chnls[channel], ispaused, .6);
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
			releaseSound(sounds[from]);
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
					releaseSound(sounds[name]);
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
	
