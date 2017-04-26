#pragma once
#include "common.h"
#include "Region.h"

class RegionState
{
public:
	RegionState();
	typedef std::vector<Region*> region_list;
	static region_list regions;
	static bool switch_music;
	static bool in_village;
	static Region current_region;
	static Region next_region;
};