#include "Region.h"
Region::Region(std::string _name, char* rtheme, char* vtheme) {
	name = _name;
	RTheme = rtheme;
	VTheme = vtheme;
}
bool Region::operator==(const Region& R) {
	return(RTheme == R.RTheme && VTheme == R.VTheme && name == R.name);
}
void Region::operator= (const Region &R) {
	RTheme = R.RTheme;
	VTheme = R.VTheme;
	name = R.name;
}