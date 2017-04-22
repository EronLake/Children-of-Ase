#include "stdafx.h"
#include "Region.h"
Region::Region(std::string _name, char* rtheme, char* vtheme, Vector2f lc) {
	name = _name;
	RTheme = rtheme;
	VTheme = vtheme;
	loc = lc;
}
bool Region::operator==(const Region& R) {
	return(RTheme == R.RTheme && VTheme == R.VTheme && name == R.name);
}
void Region::operator= (const Region &R) {
	RTheme = R.RTheme;
	VTheme = R.VTheme;
	name = R.name;
}