#pragma once
#include "Rectangle.h"
#include "Texture.h"

class Attack
{
public:
	Attack();
	Attack(int dmg, int duration, bool dstry,float w,float h,float s);
	~Attack();
	void setTexture(Texture* t) { tex = t; };
	Texture* setTexture() { return tex; };
	void setDmg(int d) { damage = d; };
	int getDmg() { return damage; };
	void setDuration(int d) { dur = d; };
	int getDuration() { return dur; };
	void setDestroy(bool d) { destroy = d; };
	bool getDestroy() { return destroy; };
	void setWidth(float w) { width = w; };
	float getWidth() { return width; };
	void setHeight(float h) { height = h; };
	float getHeight() { return height; };
	void setSpeed(float s) { speed = s; };
	float getSpeed() { return speed; };
private:
	int damage;
	int dur; 
	bool destroy;
	float width;
	float height;
	float speed;
	Texture* tex;
};

