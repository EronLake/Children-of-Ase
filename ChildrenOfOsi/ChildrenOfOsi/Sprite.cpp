#include "stdafx.h"
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
	stop = (*tex).getFrameWidth();
}

void Sprite::animate() 
{
		if (index < (*tex).getFrames()) {
			index++;
			start = (*tex).getFrameWidth()*index;
			stop = (*tex).getFrameWidth()*(index + 1);
			cout << "Animated start: " << start << " stop: " << stop << endl;
		}
		else {
			index = 0;
			start = 0;
			stop = (*tex).getFrameWidth();
		}
}

string Sprite::getTfile() 
{
	return (*tex).getFile();
}

Texture Sprite::getTexture()
{
	return *tex;
}