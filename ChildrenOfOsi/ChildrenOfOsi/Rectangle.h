#pragma once

#include "common.h"
#include "stdafx.h"
#include "Vector2f.h"
#include "Sprite.h"
#include "GameWindow.h"
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
		sprite.setTexture(tex);
		sprite.id_up=tex;
		sprite.unlockAnimation();
		sprite.setIdleTexture(sprite.id_up);
		sprite.hurt_up = texUP;
		sprite.hurt_down = texDOWN;
		sprite.hurt_right = texRIGHT;
		sprite.hurt_left = texLEFT;
		sprite.atk_up = texAtkUP;
		sprite.atk_down = texAtkDOWN;
		sprite.atk_right = texAtkRIGHT;
		sprite.atk_left = texAtkLEFT;
	}
	Rectangle() { sprite.setTexture(tex); sprite.id_up = tex;sprite.unlockAnimation();
	sprite.setIdleTexture(sprite.id_up);sprite.hurt_up = texUP;sprite.hurt_down = texDOWN;
	sprite.hurt_right = texRIGHT;sprite.hurt_left = texLEFT; sprite.atk_up = texAtkUP;
	sprite.atk_down = texAtkDOWN;sprite.atk_right = texAtkRIGHT;sprite.atk_left = texAtkLEFT;
	}
	~Rectangle() {}
	Sprite sprite;
    static Texture* tex;
	static Texture* texUP;
	static Texture* texDOWN;
	static Texture* texLEFT;
	static Texture* texRIGHT;
	static Texture* texAtkUP;
	static Texture* texAtkDOWN;
	static Texture* texAtkLEFT;
	static Texture* texAtkRIGHT;
	float getX() { return topLeft.getXloc(); }
	float getY() { return topLeft.getYloc(); }
	float getWidth() { return width; }
	float getHeight() { return height; }
	Vector2f getLoc() { return topLeft; }
	Vector2f get_mid_loc() { return {getX()+(width/2),getY()+(height / 2) }; }
	Vector2f getBL() { return{ getX()-105, getY() + height + 5 }; }
	Vector2f getTR() { return{ getX()+width+5, getY()-105 }; }
	Vector2f getBR() { return{ getX()+width+5, getY() + height+5 }; }
	void setX(float x) { topLeft.setXloc(x); }
	void setY(float y) { topLeft.setYloc(y); }
	void setWidth(float w) { width=w; }
	void setHeight(float h) { height=h; }
	void setLoc(Vector2f l) { topLeft=l; }
	Sprite getSprite() { return sprite; }
	void setSprite(Sprite s) { sprite = s; }
	void drawObj(float _x, float _y)
	{
		GameWindow::drawSprite(getX() - _x, getY() - _y, width, height, sprite);
	}
};