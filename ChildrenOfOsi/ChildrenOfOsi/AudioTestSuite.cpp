#include "stdafx.h"
#include "AudioTestSuite.h"
#include <Windows.h>

AudioTestSuite::AudioTestSuite()
{
	LOG("AudioTestSuite Object Constructed");
}


AudioTestSuite::~AudioTestSuite()
{
	LOG("AudioTestSuite Object Destroyed");
}

bool AudioTestSuite::execute_tests() {
	bool pass = true;

	if (SoundSystem_constructor_test()) {
		LOG("SoundSystem_constructor_test: " << "PASS");
	}
	else {
		LOG("SoundSystem_constructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (create_sound_test()) {
		LOG("create_sound_test: " << "PASS");
	}
	else {
		LOG("create_sound_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (play_sound_test()) {
		LOG("play_sound_test: " << "PASS");
	}
	else {
		LOG("play_sound_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------
	if (SoundSystem_destructor_test()) {
		LOG("SoundSystem_destructor_test: " << "PASS");
	}
	else {
		LOG("SoundSystem_destructor_test: " << "FAIL");
		pass = false;
	}

	//---------------------------------------------------

	return pass;
}

bool AudioTestSuite::SoundSystem_constructor_test() {
	test_soundSystem = new SoundSystem();
	if (test_soundSystem->m_pSystem == nullptr) {
		LOG("SoundSystem_constructor_test: FMOD::System not created");
		return false;
	}
	if (test_soundSystem->driverCount == 0) {
		LOG("SoundSystem_constructor_test: No system drivers");
		return false;
	}
	return true;

}

bool AudioTestSuite::SoundSystem_destructor_test() {
	delete(test_soundSystem);
	//if (test_soundSystem == nullptr) {
    return true;
	//}
	//LOG("SoundSystem_destructor_test: System not deleted properly");
	//return false;
}

bool AudioTestSuite::create_sound_test() {
	FMOD::Sound* test_address;
	std::string name = "violin.mp3";
	test_soundSystem->createSound(&test_address, name);
	auto test_sound = test_soundSystem->sounds.find(name);
	if (test_sound == test_soundSystem->sounds.end()) {
		LOG("create_sound_test: Sound not found in map");
		return false;
	}
	return true;
}

bool AudioTestSuite::play_sound_test() {
	std::string name = "violin.mp3";
	bool played = true;
	FMOD::Sound* test_sound;
	FMOD::Channel* channel = test_soundSystem->channels[0];
	test_soundSystem->playSound(test_soundSystem->sounds[name], false, channel, false);
	Sleep(6000);
	for (int i = 0; i < 32; i++) {
		test_soundSystem->channels[i]->getCurrentSound(&test_sound);
	//t	LOG("play_sound_test: channel " << i << " playing " << test_sound);
		if (test_sound == test_soundSystem->sounds[name]) return true;
	}
	channel->isPlaying(&played);
	if (played == false) {
		LOG("play_sound_test: Channel not playing any sound");
	}
	return played; 

}

//bool AudioTestSuite::channel_stress_test() {
//	return true;
//}

//bool AudioTestSuite::pause_sound_test() {

//}

// Test for looping: Have a song with known duration, check if still playing
// after duration expired
