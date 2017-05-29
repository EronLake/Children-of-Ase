#pragma once
#include "Region.h"

class RegionState
{
public:
	RegionState();
	static constexpr int MARSH = 0;
	static constexpr int DESERT = 1;
	static constexpr int MOUNTAIN = 2;
	static constexpr int JUNGLE = 3;
	
	typedef std::vector<Region*> region_list;
	static region_list regions;
	static bool switch_music;
	static bool in_village;
	static Region current_region;
	static Region next_region;
	static enum soundType { region_music, theme_music, sfx, ambient_sfx, null_type };
};