#pragma once
#include "common.h"
#include "SoundSystem.h"

class AudioTestSuite
{
public:
	AudioTestSuite();
	~AudioTestSuite();

	SoundSystem* test_soundSystem;

	bool execute_tests();

	bool SoundSystem_constructor_test();
	bool SoundSystem_destructor_test();
	bool create_sound_test();
	bool play_sound_test();
	//bool channel_stress_test();
	//bool pause_sound_test();

};

