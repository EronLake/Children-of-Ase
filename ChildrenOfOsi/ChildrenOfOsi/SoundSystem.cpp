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
		
		if (bLoop){
		channel->setLoopCount(-1);
		}
		//////cout << FMOD_ErrorString(result) << endl;
	};
	void SoundSystem::playMusic(SoundClass pSound, bool bLoop, FMOD::Channel*& channel, bool ispaused, float volume)
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
	int SoundSystem::playSong1() {
		foo::soundType type;
		FMOD::Sound* soundSample;
		const char* name;              //the variables required

		chnls[0] = nullptr;
		bool ispaused;
		unsigned int time;

		// Initialize our sound system
	
		
		type = foo::soundType::music;
		std::string _name;
		_name = "Music/RegionThemes/MarshRegion.flac";
		name = _name.c_str();
		channels[name] = &chnls[0];//assign the channel
		
		ispaused = true;

		//this->createSound(&soundSample, name);// Create the sound
		//soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

														 //SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
														 //object stuff


		playMusic(sounds[name], true, chnls[0], ispaused,.8);
		
		// Play the sound, with loop mode


		////////cout << "Press return to quit." << endl;  // Do something meanwhile...
		//cin.get();

		//releaseSound(sounds[name]); 
		return 0;// Release the sound
	};
	int SoundSystem::playSong2() {
		foo::soundType type;
		FMOD::Sound* soundSample;
		const char* name;              //the variables required

		chnls[0] = nullptr;
		bool ispaused;
		unsigned int time;

		// Initialize our sound system


		type = foo::soundType::music;
		name = "Children of Osi Sketch 2.mp3";
		channels[name] = &chnls[0];//assign the channel

		ispaused = true;

		//this->createSound(&soundSample, name);// Create the sound
		//soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

		//SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
		//object stuff


		playMusic(sounds[name], true, chnls[0], ispaused, .6);

		// Play the sound, with loop mode


		////////cout << "Press return to quit." << endl;  // Do something meanwhile...
		//cin.get();

		//releaseSound(sounds[name]); 
		return 0;// Release the sound
	};
	int SoundSystem::playSong(std::string _name) {
		foo::soundType type;
		FMOD::Sound* soundSample;
		const char* name;              //the variables required

		chnls[0] = nullptr;
		bool ispaused;
		unsigned int time;

		// Initialize our sound system


		type = foo::soundType::music;
		name = _name.c_str();
		channels[name] = &chnls[0];//assign the channel

		ispaused = true;

		//this->createSound(&soundSample, name);// Create the sound
		//soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

		//SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
		//object stuff


		playMusic(sounds[name], true, chnls[0], ispaused, .8);

		// Play the sound, with loop mode


		////////cout << "Press return to quit." << endl;  // Do something meanwhile...
		//cin.get();

		//releaseSound(sounds[name]); 
		return 0;// Release the sound
	}
	int SoundSystem::playSound(std::string _name) {
		foo::soundType type;
		FMOD::Sound* soundSample;
		const char* name;              //the variables required

		chnls[1] = nullptr;
		bool ispaused;
		unsigned int time;

		// Initialize our sound system


		type = foo::soundType::music;
		name = _name.c_str();
		channels[name] = &chnls[1];//assign the channel

		ispaused = false;

		//this->createSound(&soundSample, name);// Create the sound
		//soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

		//SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
		//object stuff


		playSound(sounds[name], false, chnls[1], ispaused, 1);

		// Play the sound, with loop mode


		////////cout << "Press return to quit." << endl;  // Do something meanwhile...
		//cin.get();

		//releaseSound(sounds[name]); 
		return 0;// Release the sound
	}
	int SoundSystem::playBump() {
		foo::soundType type;
		FMOD::Sound* soundSample;
		const char* name;              //the variables required
		chnls[1] = nullptr;
		bool ispaused;
		unsigned int time;

		// Initialize our sound system
	

		type = foo::soundType::music;
		name = "bump_0.wav";
		channels[name] = &chnls[1];//assign the channel
		ispaused = false;

		//this->createSound(&soundSample, name);// Create the sound
		//soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

		//SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
		//object stuff


		playSound(sounds[name], false, chnls[1], ispaused,1.5); 	// Play the sound, with loop mode


															////////cout << "Press return to quit." << endl;  // Do something meanwhile...
															//cin.get();

															//releaseSound(sounds[name]); 
		return 0;// Release the sound
	};
	int SoundSystem::playWalk() {
		foo::soundType type;
		FMOD::Sound* soundSample;
		const char* name;              //the variables required

		chnls[2] = nullptr;
		bool ispaused;
		unsigned int time;

		// Initialize our sound system


		type = foo::soundType::music;
		name = "SFX/walk_loop.wav";
		channels[name] = &chnls[2];//assign the channel
		ispaused = true;

		//this->createSound(&soundSample, name);// Create the sound
		//soundSample->getLength(&time, FMOD_TIMEUNIT_PCM);// Find the length

		//SoundObject* playable = new SoundObject("04.wav", &soundSample, type);
		//object stuff


		playAmbient(sounds[name], true, chnls[2], ispaused,.4); 	
// Play the sound, with loop mode


															////////cout << "Press return to quit." << endl;  // Do something meanwhile...
															//cin.get();

															//releaseSound(sounds[name]); 
		return 0;// Release the sound
	};
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
	
	
	/*void SoundSystem::playSoundObject(SoundObject sound)
	{
		FMOD::Sound* soundSample = sound.getSound();
		SoundSystem::createSound(&soundSample, sound.getName());
		bool bLoop = false;
		SoundSystem::playSound(sound.getSound(), bLoop);
		if (bLoop == false){
			// then wait until over and remove
			SoundSystem::releaseSound(sound.getSound());
		}
		

	};*/
	int SoundSystem::changeSoundSource(char* from, char* to)
	{
		
		FMOD::Channel* channel;
		string name = from;
		if ((channels[from])) {
			channel = *(channels[from]);
			bool playing = false;
			bool* isplaying = &playing;
			channel->isPlaying(isplaying);
			if (*isplaying) {
				channel->stop();
				playSong(to);

			//then play new sound
			}
		}
		return 0;
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
				channel->stop();
			}
		}
		return 0;
	};
	
	int SoundSystem::playSixers() {
		foo::soundType type;
		FMOD::Sound* soundSample;
		const char* name;              //the variables required

		chnls[0] = nullptr;
		bool ispaused;
		unsigned int time;

		// Initialize our sound system
		SoundSystem soundsystem;

		type = foo::soundType::music;
		name = "76ersAnthem.mp3";
		channels[name] = &chnls[0];//assign the channel

		ispaused = true;
		
		playMusic(sounds[name], true, chnls[0], ispaused, .6);

		return 0;// Release the sound
	};