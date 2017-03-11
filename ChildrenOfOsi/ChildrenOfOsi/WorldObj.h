#pragma once
#include "stdafx.h"
#include "common.h"
#include "Vector2f.h"
#include "Sprite.h"
#include "Rectangle.h"

using namespace std;

class WorldObj
{
public:
	WorldObj();
	WorldObj(float x,float y, bool col);
	virtual ~WorldObj();
	void setLoc(Vector2f l) { loc = l; };
	Vector2f getLoc() { return loc; };
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	void shiftX(float dist);
	void shiftY(float dist);
	void setRot(Vector2f r);
	Vector2f getRot();
	void setRotX(float x);
	void setRotY(float y);
	float getRotX();
	float getRotY();
	void shiftRotX(float dist);
	void shiftRotY(float dist);	
	void setCollision(bool c) { collision = c; };
	bool getCollision() { return collision; };
	void setInteractable(bool i) { interactable = i; };
	bool getInteractable() { return interactable; };
	void setWidth(float w);
	float getWidth() { return width; };
	void setHeight(float h);
	float getHeight() { return height; };
	Sprite getSprite() { return sprite; };
	void setSprite(Sprite s) { sprite = s; };
	void animateObj() { sprite.animate(); };
	void setName(string n) { name = n; };
	string getName() { return name; };
	WorldObj(Vector2f p_topLeft, float p_width, float p_height);
	void drawObj(float _x, float _y);
	Sprite sprite;
	//Sprite sprite_up;
	//Sprite sprite_down;
	//Sprite sprite_left;
	//Sprite sprite_right;
	vector<Rectangle> body;
	void offsetBody(int i, float x1, float x2, float y1, float y2);
	void _print();
	void setDirection(std::string d) { direction = d; };
	std::string getDirection() { return direction; };
	void setType(int t) { type = t; };
	int getType() { return type; };
	int getID() { return ID; };
private:
	int ID;
	static int idNum;
	std::string direction;
	Vector2f loc;
	Vector2f rotation;
	bool collision;
	bool interactable;
	float width;
	float height;
	string name;
	int type; //  -1: Attack, 0: WorldObj, 1: LivingObj, 2: NPC, 3: Soldier, 4: SplSoldier, 5: Hero, 6: Player
};


