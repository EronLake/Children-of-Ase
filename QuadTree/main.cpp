#include "quadtree.h"
#include "common.h"
using namespace std;

screen & placeholder obj
typedef struct Rectangle{
	pair<int,int> topLeft;
	int l, w;
	Rectangle(int x, int y, int w, int l){
		topLeft = pair<int,int>(x,y);
		w = w;
		l = l;
	}
	int getX() {return topLeft.first;}
	int getY() {return topLeft.second;}
	int getWidth() {return w;}
	int getLength() {return l;}
}Rectangle;


int main()
{
	//test tree here
	return 0;
}