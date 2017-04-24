#include "common.h"
#include "Vector2f.h"

class Region
{
private:
	char* RTheme;
	char* VTheme;
public:
	std::string name;
	Region(std::string _name, char* rtheme, char* vtheme, Vector2f lc);
	bool operator == (const Region& R);
	void operator= (const Region& R);

	char* getVTheme() { return VTheme; };
	void setVTheme(char* theme) { VTheme = theme; }
	char* getRTheme() { return RTheme; };
	void setRTheme(char* theme) { RTheme = theme; }

	Vector2f loc;
	
};