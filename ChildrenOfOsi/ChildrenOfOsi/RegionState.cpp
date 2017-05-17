#include "RegionState.h"

std::vector<Region*> make_region_vector()
{
	std::vector<Region*> r;
	r.push_back(new Region("Marsh", "Music/RegionThemes/DesertRegion.flac", "Music/HeroThemes/oya.flac", { 8000,2900 }));
	r.push_back(new Region("Desert", "Music/RegionThemes/MarshRegion.flac", "Music/HeroThemes/ogun.flac", { 5045,13465 }));
	r.push_back(new Region("Mountain", "Music/RegionThemes/MountainRegion.flac", "nothing", { 21000,4000 }));
	r.push_back(new Region("Jungle", "Music/RegionThemes/JungleRegion.flac", "Music/HeroThemes/oya.flac", { 17157,20960 }));
	return r;
}


bool RegionState::switch_music = false;
bool RegionState::in_village = false;

Region RegionState::current_region = Region("none", "none", "none",{0,0});
Region RegionState::next_region = Region("none", "none", "none",{0, 0});

RegionState::region_list RegionState::regions = make_region_vector();

RegionState::RegionState() {
	
}