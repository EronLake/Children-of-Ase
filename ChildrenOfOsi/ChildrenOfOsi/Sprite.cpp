#include "Sprite.h"

using namespace std;

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::setTexture(Texture *t)
{
	tex = t;
	index = 0;
	start = 0;
	stop = (*tex).getFWidth();
}

void Sprite::animate() 
{
	if ((*tex).getAnimated()) {
		if (index < (*tex).getFrames()) {
			index++;
			start = (*tex).getFWidth()*(float)index;
			stop = (*tex).getFWidth()*(float)(index + 1);
			cout << "Animated start: " << start << " stop: " << stop << endl;
		}
		else {
			index = 0;
			start = 0;
			stop = (*tex).getFWidth();
		}
	}
}