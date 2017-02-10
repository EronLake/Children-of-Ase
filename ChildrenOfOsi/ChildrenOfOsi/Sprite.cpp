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
	top = (*tex).getHeight();
	bottom = 0;
	tempTime = 0;
}

void Sprite::animate() 
{
	tempTime++;
	if (tempTime==30) {
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
		tempTime = 0;
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

float Sprite::getStart()
{
	return start;
}

float Sprite::getStop()
{
	return stop;
}

float Sprite::getTop()
{
	return top;
}

float Sprite::getBottom()
{
	return bottom;
}