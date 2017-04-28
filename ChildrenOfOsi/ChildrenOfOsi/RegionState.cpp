#include "RegionState.h"

std::vector<Region*> make_region_vector()
{
	std::vector<Region*> r;
	RegionState::regions.push_back(new Region("Marsh", "Music/RegionThemes/MarshRegion.flac", "Music/HeroThemes/ogun.flac", { 1000, 1000}));
	RegionState::regions.push_back(new Region("Mountain", "Music/RegionThemes/MountainRegion.flac", "nothing", { 5000,5000 }));
	RegionState::regions.push_back(new Region("Jungle", "Music/RegionThemes/JungleRegion.flac", "Music/HeroThemes/oya.flac", { 10000,1000 }));
	RegionState::regions.push_back(new Region("Desert", "Music/RegionThemes/DesertRegion.flac", "Music/HeroThemes/oya.flac", { 5000,10000 }));
	return r;
}

bool RegionState::switch_music = false;
bool RegionState::in_village = false;

Region RegionState::current_region = Region("none", "none", "none",{0,0});
Region RegionState::next_region = Region("none", "none", "none",{0, 0});

RegionState::region_list RegionState::regions = make_region_vector();

RegionState::RegionState() {
	
}