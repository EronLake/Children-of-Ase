#include "stdafx.h"
#include "RegionState.h"


std::vector<Region*> make_region_vector()
{
	std::vector<Region*> r;
	r.push_back(new Region("Marsh", "../ChildrenofOsi/Music/RegionThemes/DesertRegion.flac", "Music/HeroThemes/oya.flac", { 8000,2900 }));
	r.push_back(new Region("Desert", "../ChildrenofOsi/Music/RegionThemes/DesertRegion.flac", "Music/HeroThemes/ogun.flac", { 5045,13465 }));
	r.push_back(new Region("Mountain", "../ChildrenofOsi/Music/RegionThemes/MountainRegion.flac", "nothing", { 21000,4000 }));
	r.push_back(new Region("Jungle", "../ChildrenofOsi/Music/RegionThemes/JungleRegion.flac", "Music/HeroThemes/oya.flac", { 17615, 21480 }));
	return r;
};


bool RegionState::switch_music = false;
bool RegionState::in_village = false;
bool RegionState::in_combat = false;

Region RegionState::current_region = Region("none", "none", "none",{0,0});
Region RegionState::next_region = Region("none", "none", "none",{0, 0});
Hero* RegionState::current_hero = nullptr;

RegionState::region_list RegionState::regions = make_region_vector();

RegionState::RegionState() {
	
};