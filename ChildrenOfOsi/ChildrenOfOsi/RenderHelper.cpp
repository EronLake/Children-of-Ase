#include "stdafx.h"
#include "RenderHelper.h"
#include <algorithm>
#include <vector> 
#include "RenderManager.h"


RenderHelper::RenderHelper(QuadTree * QT)
{
	tree = QT;
	camera = new WorldObj(0, 0, false);
	fullBound = new WorldObj(Vector2f(0, 0), 20000, 20000);
	cameraSize.setXloc(960);
	cameraSize.setYloc(540);
	mapSize.setXloc(20000);	//10000
	mapSize.setYloc(20000);	//10000
	convoGui = new DialogueGui();
	convoGui->loadTexture();
	convoGui->setSprite();
	hud_ptr = new HUD();
	hud_ptr->loadTexture();
	hud_ptr->setSprite();
	gmap = new GameMap();
	//fullVec = tree->retrieve(fullVec, fullBound);
	//	gmap->loadTexture();
	//	gmap->setSprite();
}

RenderHelper::~RenderHelper()
{
}

void RenderHelper::initCamera(WorldObj * player)
{
	//if player is within the four corners of the screen, camera is just the four corner of the screen
	float camX = player->getX() - ((cameraSize.getXloc() / 2)*map_zoom) - (player->getWidth() / 2);
	float camY = player->getY() - ((cameraSize.getYloc() / 2)*map_zoom) + (player->getHeight() / 2);
	camera->setLoc(Vector2f(camX, camY));
	camera->setWidth(cameraSize.getXloc() + 700);
	camera->setHeight(cameraSize.getYloc() + 300);
	cout << "Camera has coord " << camera->getX() << ", " << camera->getY() << " and width and height of " << camera->getWidth() << ", " << camera->getHeight() << endl;


}

void RenderHelper::initCameraFull(WorldObj * player)
{

}

int RenderHelper::init_map(WorldObj* obj)
{
	gmap->setTextures();
	gmap->loadTexture();
	gmap->setSprite();

	return 0;
}

// Don't need to pass in obj to draw frame, but will pass in to keep consistent style in map and pass in player to get camera coord.
int RenderHelper::draw_frame(WorldObj * obj)
{
	initCamera(obj);
	//pass in the camera bound for rendering instead of the object
	objVec.clear();
	fullVec.clear();

	//objVec = tree->retrieve(objVec, camera);
	if (fullVec.empty()) {
		fullVec = tree->retrieve(fullVec, fullBound);
	}

	
	for (int i = 0; i < fullVec.size(); i++) {
		WorldObj* tempObj = fullVec[i];
		if (tempObj->getX() > obj->getX() - 1000 && tempObj->getX() < obj->getX() + 1000 && tempObj->getY() > obj->getY() - 800 && tempObj->getY() < obj->getY() + 800) {
				auto it = std::find(objVec.begin(), objVec.end(), tempObj);
				if (it == objVec.end()) {
					objVec.push_back(tempObj);
				}
		}	
		
	}

	//cout << "SIZE OF THE RENDER OBJVEC IS RENDEREDNEREDNEREDNER *** " << objVec.size() << endl;
	gmap->drawMap(camera->getX(), camera->getY());
	//obj->WorldObj::drawObj(camera->getX(), camera->getY());
	//obj->WorldObj::animateObj();
	objVec.push_back(obj);
	//unordered_map<WorldObj*, int> tempmap;

	//for (auto it = objVec.begin(); it != objVec.end(); it++) {
	//	if (tempmap.find(*it) != tempmap.end()) {
	//		cout << "WE HAVE REPEATED OBJ IN THE OBJVEC!!!!!!!!!!!!!!!!!!!!!**********************" << endl;
	//	}
	//	else {
	//		tempmap[*it] = 1;
	//	}
	//}
	//cout << "SIZE OF ATTACK TABLE IS " << Containers::Attack_table.size() << endl;
	for (auto i = Containers::Attack_table.begin(); i != Containers::Attack_table.end(); ++i) {
		if (i->second->getPause() == 0) {
			objVec.push_back(i->second);
		}
	}
	/*for (int i = 0; i < obj->body.size(); i++) {
		osi::GameWindow::drawSprite(obj->body[i].getX()-camera->getX(), obj->body[i].getY()-camera->getY(), obj->body[i].getWidth(), obj->body[i].getHeight(), obj->getSprite());
	}*/
	sortVec();
	////cout << "******************************************SIZE OF THE OBJVEC TO RENDER IS " << objVec.size() << endl;
	for (int i = 0; i < objVec.size(); i++) {
		
		if (objVec[i]->getType() == 3) {
			if (CheckClass::isSoldier(objVec[i])->getHealth() > 0) {
				LOG("BEFORE DRAWING**");
				//////cout << objVec[i]->getX() - camera->getX() << endl;
				//LOG(objVec[i]->getX(), ", ", objVec[i]->getY());
				objVec[i]->WorldObj::drawObj(camera->getX(), camera->getY());
				//for (int j = 0; j < objVec[i]->body.size(); j++) {
				objVec[i]->body[0].drawObj(camera->getX(), camera->getY());
				objVec[i]->effect.drawObj(camera->getX(), camera->getY());
				//}
				objVec[i]->effect.sprite.animate();
				objVec[i]->WorldObj::animateObj();
			}
		}
		else {
			LOG("BEFORE DRAWING**");
			//////cout << objVec[i]->getX() - camera->getX() << endl;
			//LOG(objVec[i]->getX(), ", ", objVec[i]->getY());
			objVec[i]->WorldObj::drawObj(camera->getX(), camera->getY());
			//for (int j = 0; j < objVec[i]->body.size(); j++) {
			objVec[i]->body[0].drawObj(camera->getX(), camera->getY());
			objVec[i]->effect.drawObj(camera->getX(), camera->getY());
			//}
			objVec[i]->effect.sprite.animate();
			objVec[i]->WorldObj::animateObj();
		}
	}
	//convoGui->drawGui();
	drawHUD(obj);
	osi::GameWindow::refresh();
	return 0;
}


int RenderHelper::drawDiaGui(WorldObj* obj)
{
	gmap->drawMap(camera->getX(), camera->getY());
	obj->WorldObj::drawObj(camera->getX(), camera->getY());
	obj->WorldObj::animateObj();
	for (int i = 0; i < objVec.size(); i++) {
		LOG("BEFORE DRAWING**");
		//////cout << objVec[i]->getX() - camera->getX() << endl;
		//LOG(objVec[i]->getX(), ", ", objVec[i]->getY());
		objVec[i]->WorldObj::drawObj(camera->getX(), camera->getY());
		objVec[i]->WorldObj::animateObj();
	}
	convoGui->drawGui();
	osi::GameWindow::refresh();
	return 0;
}

int RenderHelper::drawHUD(WorldObj* obj)
{
	hud_ptr->drawHUD(obj);
	return 0;
}


int RenderHelper::setSwordGlow(WorldObj * obj)
{
	convoGui->setSwordGlow();
	return 0;
}

int RenderHelper::setHeartGlow(WorldObj * obj)
{
	convoGui->setHeartGlow();
	return 0;
}

int RenderHelper::setFaceGlow(WorldObj * obj)
{
	convoGui->setFaceGlow();
	return 0;
}

int RenderHelper::setQuestionGlow(WorldObj * obj)
{
	convoGui->setQuestionGlow();
	return 0;
}


int RenderHelper::sprite_up(WorldObj * obj)
{
	obj->sprite.setTexture(obj->sprite.up);
	obj->sprite.setIdleTexture(obj->sprite.id_up);
	return 0;
}

int RenderHelper::sprite_down(WorldObj* obj) {
	obj->sprite.setTexture(obj->sprite.down);
	obj->sprite.setIdleTexture(obj->sprite.id_down);
	return 0;
}

int RenderHelper::sprite_left(WorldObj* obj) {
	obj->sprite.setTexture(obj->sprite.left);
	obj->sprite.setIdleTexture(obj->sprite.id_left);
	return 0;
}

int RenderHelper::sprite_right(WorldObj* obj) {
	obj->sprite.setTexture(obj->sprite.right);
	obj->sprite.setIdleTexture(obj->sprite.id_right);
	return 0;
}

int RenderHelper::sprite_atk(WorldObj * o)
{
	if (o->getType() > 2) {
		Soldier* obj = CheckClass::isSoldier(o);
		int check = obj->getDirection();
		if (check == 8) {
			if (obj->getSwingLeft()) {
				obj->sprite.setTexture(obj->sprite.atk_up);
				//obj->effect.sprite.setTexture(obj->effect.sprite.atk_up);
				manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
			}
			else {
				obj->sprite.setTexture(obj->sprite.atk2_up);
				manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
			}
			obj->sprite.setIdleTexture(obj->sprite.id_up);
		}
		else 	if (check == 2) {
			if (obj->getSwingLeft()) {
				obj->sprite.setTexture(obj->sprite.atk_down);
			//	obj->effect.sprite.setTexture(obj->effect.sprite.atk_down);
				manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
			}
			else {
				obj->sprite.setTexture(obj->sprite.atk2_down);
				manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
			}
			obj->sprite.setIdleTexture(obj->sprite.id_down);

		}
		else 	if (check == 6) {
			if (obj->getSwingLeft()) {

				obj->sprite.setTexture(obj->sprite.atk_right);
				//obj->effect.sprite.setTexture(obj->effect.sprite.atk_right);
				manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
			}
			else {
				obj->sprite.setTexture(obj->sprite.atk2_right);
				manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
			}
			obj->sprite.setIdleTexture(obj->sprite.id_right);
		}
		else	if (check == 4) {
			if (obj->getSwingLeft()) {
				obj->sprite.setTexture(obj->sprite.atk_left);
				//obj->effect.sprite.setTexture(obj->effect.sprite.atk_left);
				manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
			}
			else {
				obj->sprite.setTexture(obj->sprite.atk2_left);
				manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav");
			}
			obj->sprite.setIdleTexture(obj->sprite.id_left);
		}
		obj->sprite.lockAnimation();
		obj->effect.sprite.lockAnimation();
	}
	return 0;
}

int RenderHelper::sprite_spin_atk(WorldObj * o)
{
	if (o->getType() > 2) {
		Soldier* obj = CheckClass::isSoldier(o);
		int check = obj->getDirection();
		if (check == 8) {
			obj->sprite.setTexture(obj->sprite.spin_up);
			obj->sprite.setIdleTexture(obj->sprite.id_up);
		}
		else 	if (check == 2) {
			obj->sprite.setTexture(obj->sprite.spin_down);
			obj->sprite.setIdleTexture(obj->sprite.id_down);
		}
		else 	if (check == 6) {
			obj->sprite.setTexture(obj->sprite.spin_right);
			obj->sprite.setIdleTexture(obj->sprite.id_right);
		}
		else	if (check == 4) {
			obj->sprite.setTexture(obj->sprite.spin_left);
			obj->sprite.setIdleTexture(obj->sprite.id_left);
		}
		obj->sprite.lockAnimation();
	}
	return 0;
}

int RenderHelper::sprite_fire_atk(WorldObj * o)
{
	if (o->getType() > 2) {
		Soldier* obj = CheckClass::isSoldier(o);
		int check = obj->getDirection();
		if (check == 8) {
			obj->sprite.setTexture(obj->sprite.breathe_up);
			obj->sprite.setIdleTexture(obj->sprite.id_up);
		}
		else 	if (check == 2) {
			obj->sprite.setTexture(obj->sprite.breathe_down);
			obj->sprite.setIdleTexture(obj->sprite.id_down);
		}
		else 	if (check == 6) {
			obj->sprite.setTexture(obj->sprite.breathe_right);
			obj->sprite.setIdleTexture(obj->sprite.id_right);
		}
		else	if (check == 4) {
			obj->sprite.setTexture(obj->sprite.breathe_left);
			obj->sprite.setIdleTexture(obj->sprite.id_left);
		}
		obj->sprite.lockAnimation();
	}
	return 0;
}

int RenderHelper::sprite_hurt(WorldObj * obj)
{
	int check = obj->getDirection();
	obj->sprite.unlockAnimation();
	obj->sprite.setTexture(obj->sprite.id_up);
	obj->effect.sprite.unlockAnimation();
	obj->effect.sprite.setTexture(obj->effect.sprite.id_up);
	if (check == 8) {
		obj->sprite.setTexture(obj->sprite.hurt_up);
		obj->sprite.setIdleTexture(obj->sprite.id_up);
		obj->effect.sprite.setTexture(obj->effect.sprite.hurt_up);
	}
	else 	if (check == 2) {
		obj->sprite.setTexture(obj->sprite.hurt_down);
		obj->sprite.setIdleTexture(obj->sprite.id_down);
		obj->effect.sprite.setTexture(obj->effect.sprite.hurt_down);
	}
	else 	if (check == 6) {
		obj->sprite.setTexture(obj->sprite.hurt_right);
		obj->sprite.setIdleTexture(obj->sprite.id_right);
		obj->effect.sprite.setTexture(obj->effect.sprite.hurt_right);
	}
	else	if (check == 4) {
		obj->sprite.setTexture(obj->sprite.hurt_left);
		obj->sprite.setIdleTexture(obj->sprite.id_left);
		obj->effect.sprite.setTexture(obj->effect.sprite.hurt_left);
	}
	obj->sprite.lockAnimation();
	obj->effect.sprite.lockAnimation();
	return 0;
}

int RenderHelper::sprite_idle(WorldObj* obj) {
	//if (!obj->sprite.isIdle()) {
	obj->sprite.setTexture((obj->sprite.getIdleTexture()));
	//}
	return 0;
}

int RenderHelper::sprite_update(WorldObj * obj)
{
	return 0;
}

void RenderHelper::sortVec()
{
	sort(objVec.begin(), objVec.end(), [](WorldObj* a, WorldObj* b) {
		return ((a->body[0].getY() + a->body[0].getHeight()) < (b->body[0].getY() + b->body[0].getHeight()));
	});
}

bool RenderHelper::compY(WorldObj* a, WorldObj* b) {
	return ((a->getY() + a->getHeight()) < (b->getY() + b->getHeight()));
}

