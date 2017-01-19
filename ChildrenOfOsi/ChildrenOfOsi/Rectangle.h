#include "common.h"
#include "Vector2f.h"
using namespace std;

class Rectangle
{
private:
	Vector2f topLeft;
	float width, height;
public:
	Rectangle(Vector2f p_topLeft, float p_width, float p_height) {
		topLeft = p_topLeft;
		width = p_width;
		height = p_height;
	}
	~Rectangle() {}
	float getX() { return topLeft.getXloc(); }
	float getY() { return topLeft.getYloc(); }
	float getWidth() { return width; }
	float getHeight() { return height; }

};