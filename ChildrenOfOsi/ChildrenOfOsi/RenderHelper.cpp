#include "stdafx.h"
#include "RenderHelper.h"
#include <algorithm>
#include <vector> 
#include "RenderManager.h"
#include "Tutorial.h"

GameMap* RenderHelper::gmap;


RenderHelper::RenderHelper(QuadTree * QT, RiverObj* _rivObj, std::vector<WorldObj*>* _largeStruct, UniformGrid<WorldObj>* _worldobj_grid)
{
  tree = QT;
  rivObj = _rivObj;
  largeStruct = _largeStruct;
  grid_game = _worldobj_grid;
  camera = new WorldObj(0, 0, false);
  fullBound = new WorldObj(Vector2f(0, 0), 25000, 25000);
  cameraSize.setXloc(960);
  cameraSize.setYloc(540);
  mapSize.setXloc(25000);	//10000
  mapSize.setYloc(25000);	//10000
  convoGui = new DialogueGui();
  convoGui->loadTexture();
  convoGui->setSprite();
  hud_ptr = new HUD();
  hud_ptr->loadTexture();
  hud_ptr->setSprite();
  gmap = new GameMap();
  TutGui = new Rectangle(Vector2f(cameraSize.xloc / 4, cameraSize.yloc / 8), cameraSize.xloc / 2, cameraSize.yloc / 1.5);
  logo_gui = new Rectangle(Vector2f(0.0F, 0.0F), cameraSize.xloc, cameraSize.yloc);
  victory_menu = new Rectangle(Vector2f(0.0F, 0.0F), cameraSize.xloc, cameraSize.yloc);
  initTutGui();
  init_logo_gui();
  init_victory_menu_gui();
  //fullVec = tree->retrieve(fullVec, fullBound);
  //	gmap->loadTexture();
  //	gmap->setSprite();
}

RenderHelper::~RenderHelper()
{}

void RenderHelper::initCamera(WorldObj * player)
{
  //if player is within the four corners of the screen, camera is just the four corner of the screen

  float camX = player->getX() - ((cameraSize.getXloc() / 2)*map_zoom) + (player->getWidth() / 2);
  float camY = player->getY() - ((cameraSize.getYloc() / 2)*map_zoom) + (player->getHeight() / 2);
  camera->setLoc(Vector2f(camX, camY));
  camera->setWidth(cameraSize.getXloc() + 480);	//700
  camera->setHeight(cameraSize.getYloc() + 270);	//300
  ////cout << "Camera has coord " << camera->getX() << ", " << camera->getY() << " and width and height of " << camera->getWidth() << ", " << camera->getHeight() << endl;

}

void RenderHelper::initCameraFull(WorldObj * player)
{
	Texture* victory_menu_tex = new Texture();
	victory_menu_tex->setFile("Assets/Sprites/Victory_Menu.png", 1);
	victory_menu->sprite.setTexture(victory_menu_tex);
}

void RenderHelper::initTutGui()
{
  Texture* tutTex = new Texture();
  tutTex->setFile("Assets/Sprites/Tutorial.png", 1);
  TutGui->sprite.setTexture(tutTex);
}

void RenderHelper::init_logo_gui()
{
  Texture* logo_tex = new Texture();
  logo_tex->setFile("Assets/Sprites/Logo_Loading.png", 1);
  logo_gui->sprite.setTexture(logo_tex);
}

void RenderHelper::init_victory_menu_gui()
{
}

int RenderHelper::init_map(WorldObj* obj)
{
	gmap->setTextures();
	gmap->loadTexture({0,0});
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
		//fullVec = tree->retrieve(fullVec, fullBound);
		fullVec = grid_game->retrieve_worldobj_in_grid(fullVec, obj);
	}

	//set<WorldObj*> s;
	//unsigned size = fullVec.size();
	//for (unsigned i = 0; i < size; ++i) s.insert(fullVec[i]);
	//fullVec.assign(s.begin(), s.end());

	//cout << "size of fullvec is " << fullVec.size() << endl;
	for (int i = 0; i < fullVec.size(); i++) {
		WorldObj* tempObj = fullVec[i];
		objVec.push_back(tempObj);

		////1k pixels left and rigfht, 800 pixels up and down. OBJS WHOSE WIDTH AND HEIGHT ARE GREATER THAN 1-2k and 800-1.6k respectively DO NOT FUNCTION CORRECTLY
		//if (tempObj->getX() > obj->getX() - (1000*map_zoom) && tempObj->getX() < obj->getX() + (1000*map_zoom) && tempObj->getY() > obj->getY() - (800*map_zoom) && tempObj->getY() < obj->getY() + (800*map_zoom)) {
		//		auto it = std::find(objVec.begin(), objVec.end(), tempObj);
		//		if (it == objVec.end()) {
		//			objVec.push_back(tempObj);
		//		}
		//}	
		
	}

	////cout << "SIZE OF THE RENDER OBJVEC IS RENDEREDNEREDNEREDNER *** " << objVec.size() << endl;
	gmap->drawMap(camera->getX(), camera->getY());
	//obj->WorldObj::drawObj(camera->getX(), camera->getY());
	//obj->WorldObj::animateObj();
	objVec.push_back(obj);
	//unordered_map<WorldObj*, int> tempmap;

	//for (auto it = objVec.begin(); it != objVec.end(); it++) {
	//	if (tempmap.find(*it) != tempmap.end()) {
	//		//cout << "WE HAVE REPEATED OBJ IN THE OBJVEC!!!!!!!!!!!!!!!!!!!!!**********************" << endl;
	//	}
	//	else {
	//		tempmap[*it] = 1;
	//	}
	//}
	////cout << "SIZE OF ATTACK TABLE IS " << Containers::Attack_table.size() << endl;
	for (auto i = Containers::Attack_table.begin(); i != Containers::Attack_table.end(); ++i) {
		if (i->second->getPause() == 0) {
			objVec.push_back(i->second);
		}
	}
	/*for (int i = 0; i < obj->body.size(); i++) {
		osi::GameWindow::drawSprite(obj->body[i].getX()-camera->getX(), obj->body[i].getY()-camera->getY(), obj->body[i].getWidth(), obj->body[i].getHeight(), obj->getSprite());
	}*/
	sortVec();
	for (int i = 0; i < largeStruct->size(); i++) {
		WorldObj* tempObj = (*largeStruct)[i];
		//1k pixels left and rigfht, 800 pixels up and down. OBJS WHOSE WIDTH AND HEIGHT ARE GREATER THAN 1-2k and 800-1.6k respectively DO NOT FUNCTION CORRECTLY
		if (tempObj->getX() > obj->getX() - (6000 * map_zoom) && tempObj->getX() < obj->getX() + (6000 * map_zoom) && tempObj->getY() > obj->getY() - (6000 * map_zoom) && tempObj->getY() < obj->getY() + (6000 * map_zoom)) {
			objVec.insert(objVec.begin(), tempObj);
		}
	}
	//cout << "THE COORDINATES OF OBJ IS " << obj->getX() << ", " << obj->getY() << endl;
	//cout << "******************************************SIZE OF THE OBJVEC TO RENDER IS " << objVec.size() << endl;
	//cout << "objvec size is " << objVec.size() << endl;
	for (int i = 0; i < objVec.size(); i++) {
		Soldier* temp = CheckClass::isSoldier(objVec[i]);
		if (temp) {
			if (temp->getParty()->get_hide()) continue;
		}
	//	if (objVec[i]->getName() == "rec_OT") {
		//	cout << "found tower rec render!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			//system("PAUSE");
	//	}
			LOG("BEFORE DRAWING**");
			////////cout << objVec[i]->getX() - camera->getX() << endl;
			//LOG(objVec[i]->getX(), ", ", objVec[i]->getY());
			objVec[i]->WorldObj::drawObj(camera->getX(), camera->getY());
			//Player* player = CheckClass::isPlayer(objVec[i]);
			//if (player) {
			//	if (player->can_move == false) continue;
			//}
			//for (int j = 0; j < objVec[i]->body.size(); j++) {
			objVec[i]->body[0].drawObj(camera->getX(), camera->getY());
			objVec[i]->effect.drawObj(camera->getX(), camera->getY());
			//}
			//objVec[i]->effect.sprite.animate();
			//objVec[i]->WorldObj::animateObj();
	}
	// draw the points
	//for (int i = 0; i < rivObj->getLines().size(); i++) {
	//	//cout << "DRAWING POINTS" << endl;
	//	rivObj->getLines()[i]->getP1().drawObjRiv(camera->getX(), camera->getY());
	//	rivObj->getLines()[i]->getP2().drawObjRiv(camera->getX(), camera->getY());
	//}

	//convoGui->drawGui();
	drawHUD(obj);
	GameWindow::refresh();
	return 0;
}


int RenderHelper::drawDiaGui(WorldObj* obj)
{
  gmap->drawMap(camera->getX(), camera->getY());
  obj->WorldObj::drawObj(camera->getX(), camera->getY());
  //obj->WorldObj::animateObj();
  for(int i = 0; i < objVec.size(); i++) {
    LOG("BEFORE DRAWING**");
	Soldier* temp = CheckClass::isSoldier(objVec[i]);
	if (temp) {
		if (temp->getParty()->get_hide()) continue;
	}
    ////////cout << objVec[i]->getX() - camera->getX() << endl;
    //LOG(objVec[i]->getX(), ", ", objVec[i]->getY());
    objVec[i]->WorldObj::drawObj(camera->getX(), camera->getY());
    //objVec[i]->WorldObj::animateObj();
  }
  convoGui->drawGui();
  drawHUD(obj);
  GameWindow::refresh();
  return 0;
}


int RenderHelper::drawHUD(WorldObj* obj)
{
  hud_ptr->drawHUD(obj);
  return 0;
}

int RenderHelper::drawTut(WorldObj *obj)
{
  gmap->drawMap(camera->getX(), camera->getY());
  obj->WorldObj::drawObj(camera->getX(), camera->getY());
  obj->WorldObj::animateObj();

  objVec = grid_game->retrieve_worldobj_in_grid(objVec, obj);
  for (int i = 0; i < objVec.size(); ++i) {
    Soldier *sold = CheckClass::isSoldier(objVec[i]);
    if(sold) {
      if(sold->get_incapacitated()) {
        objVec[i]->WorldObj::drawObj(camera->getX(), camera->getY());
        objVec[i]->WorldObj::animateObj();
      }
    }
    else {
      objVec[i]->WorldObj::drawObj(camera->getX(), camera->getY());
      objVec[i]->WorldObj::animateObj();
    }
  }

  TutGui->drawObj(camera->getX(), camera->getY());
  Tutorial::drawTutorial();

  GameWindow::refresh();
  return 0;
}

int RenderHelper::draw_logo(WorldObj * obj)
{
  logo_gui->drawObj(camera->getX(), camera->getY());
  GameWindow::refresh();
  return 0;
}

int RenderHelper::draw_victory_menu(WorldObj * obj)
{
	victory_menu->drawObj(camera->getX(), camera->getY());
	GameWindow::refresh();
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

int RenderHelper::sprite_down(WorldObj* obj)
{
  obj->sprite.setTexture(obj->sprite.down);
  obj->sprite.setIdleTexture(obj->sprite.id_down);
  return 0;
}

int RenderHelper::sprite_left(WorldObj* obj)
{
  obj->sprite.setTexture(obj->sprite.left);
  obj->sprite.setIdleTexture(obj->sprite.id_left);
  return 0;
}

int RenderHelper::sprite_right(WorldObj* obj)
{
  obj->sprite.setTexture(obj->sprite.right);
  obj->sprite.setIdleTexture(obj->sprite.id_right);
  return 0;
}

int RenderHelper::sprite_atk(WorldObj * o)
{
  if(o->getType() >= WorldObj::TYPE_SOLDIER) {
    Soldier* obj = CheckClass::isSoldier(o);
    switch(obj->getDirection()) {
      case WorldObj::DIRECTION_UP:
        if(obj->getSwingLeft()) {
          obj->sprite.setTexture(obj->sprite.atk_up);
          //obj->effect.sprite.setTexture(obj->effect.sprite.atk_up);
          manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav",nullptr, RegionState::soundType::sfx);
        }
        else {
          obj->sprite.setTexture(obj->sprite.atk2_up);
          manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav", nullptr, RegionState::soundType::sfx);
        }
        obj->sprite.setIdleTexture(obj->sprite.id_up);
        break;
      case WorldObj::DIRECTION_DOWN:
        if(obj->getSwingLeft()) {
          obj->sprite.setTexture(obj->sprite.atk_down);
          //	obj->effect.sprite.setTexture(obj->effect.sprite.atk_down);
          manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav", nullptr, RegionState::soundType::sfx);
        }
        else {
          obj->sprite.setTexture(obj->sprite.atk2_down);
          manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav", nullptr, RegionState::soundType::sfx);
        }
        obj->sprite.setIdleTexture(obj->sprite.id_down);

        break;
      case WorldObj::DIRECTION_RIGHT:
        if(obj->getSwingLeft()) {

          obj->sprite.setTexture(obj->sprite.atk_right);
          //obj->effect.sprite.setTexture(obj->effect.sprite.atk_right);
          manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav", nullptr, RegionState::soundType::sfx);
        }
        else {
          obj->sprite.setTexture(obj->sprite.atk2_right);
          manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav", nullptr, RegionState::soundType::sfx);
        }
        obj->sprite.setIdleTexture(obj->sprite.id_right);
        break;
      case WorldObj::DIRECTION_LEFT:
        if(obj->getSwingLeft()) {
          obj->sprite.setTexture(obj->sprite.atk_left);
          //obj->effect.sprite.setTexture(obj->effect.sprite.atk_left);
          manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav", nullptr, RegionState::soundType::sfx);
        }
        else {
          obj->sprite.setTexture(obj->sprite.atk2_left);
          manager->createTaskForAudio("PlaySound", "SOUND", "SFX/swing.wav", nullptr, RegionState::soundType::sfx);
        }
        obj->sprite.setIdleTexture(obj->sprite.id_left);
        break;
    }
    obj->sprite.lockAnimation();
    obj->effect.sprite.lockAnimation();
  }
  return 0;
}

int RenderHelper::sprite_spin_atk(WorldObj * o)
{
  if(o->getType() >= WorldObj::TYPE_SOLDIER) {
    Soldier* obj = CheckClass::isSoldier(o);
    switch(obj->getDirection()) {
      case WorldObj::DIRECTION_UP:
        obj->sprite.setTexture(obj->sprite.spin_up);
        obj->sprite.setIdleTexture(obj->sprite.id_up);
        break;
      case WorldObj::DIRECTION_DOWN:
        obj->sprite.setTexture(obj->sprite.spin_down);
        obj->sprite.setIdleTexture(obj->sprite.id_down);
        break;
      case WorldObj::DIRECTION_RIGHT:
        obj->sprite.setTexture(obj->sprite.spin_right);
        obj->sprite.setIdleTexture(obj->sprite.id_right);
        break;
      case WorldObj::DIRECTION_LEFT:
        obj->sprite.setTexture(obj->sprite.spin_left);
        obj->sprite.setIdleTexture(obj->sprite.id_left);
        break;
    }
    obj->sprite.lockAnimation();
  }
  return 0;
}

int RenderHelper::sprite_fire_atk(WorldObj * o)
{
  if(o->getType() >= WorldObj::TYPE_SOLDIER) {
    Soldier* obj = CheckClass::isSoldier(o);
    switch(obj->getDirection()) {
      case WorldObj::DIRECTION_UP:
        obj->sprite.setTexture(obj->sprite.breathe_up);
        obj->sprite.setIdleTexture(obj->sprite.id_up);
        break;
      case WorldObj::DIRECTION_DOWN:
        obj->sprite.setTexture(obj->sprite.breathe_down);
        obj->sprite.setIdleTexture(obj->sprite.id_down);
        break;
      case WorldObj::DIRECTION_RIGHT:
        obj->sprite.setTexture(obj->sprite.breathe_right);
        obj->sprite.setIdleTexture(obj->sprite.id_right);
        break;
      case WorldObj::DIRECTION_LEFT:
        obj->sprite.setTexture(obj->sprite.breathe_left);
        obj->sprite.setIdleTexture(obj->sprite.id_left);
        break;
    }
    obj->sprite.lockAnimation();
  }
  return 0;
}

int RenderHelper::sprite_hurt(WorldObj * obj)
{
  obj->sprite.unlockAnimation();
  obj->sprite.setTexture(obj->sprite.id_up);
  obj->effect.sprite.unlockAnimation();
  obj->effect.sprite.setTexture(obj->effect.sprite.id_up);
  switch(obj->getDirection()) {
    case WorldObj::DIRECTION_UP:
      obj->sprite.setTexture(obj->sprite.hurt_up);
      obj->sprite.setIdleTexture(obj->sprite.id_up);
      obj->effect.sprite.setTexture(obj->effect.sprite.hurt_up);
      break;
    case WorldObj::DIRECTION_DOWN:
      obj->sprite.setTexture(obj->sprite.hurt_down);
      obj->sprite.setIdleTexture(obj->sprite.id_down);
      obj->effect.sprite.setTexture(obj->effect.sprite.hurt_down);
      break;
    case WorldObj::DIRECTION_RIGHT:
      obj->sprite.setTexture(obj->sprite.hurt_right);
      obj->sprite.setIdleTexture(obj->sprite.id_right);
      obj->effect.sprite.setTexture(obj->effect.sprite.hurt_right);
      break;
    case WorldObj::DIRECTION_LEFT:
      obj->sprite.setTexture(obj->sprite.hurt_left);
      obj->sprite.setIdleTexture(obj->sprite.id_left);
      obj->effect.sprite.setTexture(obj->effect.sprite.hurt_left);
      break;
  }
  obj->sprite.lockAnimation();
  obj->effect.sprite.lockAnimation();
  return 0;
}

int RenderHelper::sprite_dead(WorldObj * obj)
{
  obj->sprite.unlockAnimation();
  obj->sprite.setTexture(obj->sprite.id_up);
  obj->effect.sprite.unlockAnimation();
  obj->effect.sprite.setTexture(obj->effect.sprite.id_up);
  switch(obj->getDirection()) {
    case WorldObj::DIRECTION_UP:
      obj->sprite.setTexture(obj->sprite.death_up);
      obj->sprite.setIdleTexture(obj->sprite.id_up);
      obj->effect.sprite.setTexture(obj->effect.sprite.hurt_up);
      break;
    case WorldObj::DIRECTION_DOWN:
      obj->sprite.setTexture(obj->sprite.death_down);
      obj->sprite.setIdleTexture(obj->sprite.id_down);
      obj->effect.sprite.setTexture(obj->effect.sprite.hurt_down);
      break;
    case WorldObj::DIRECTION_RIGHT:
      obj->sprite.setTexture(obj->sprite.death_right);
      obj->sprite.setIdleTexture(obj->sprite.id_right);
      obj->effect.sprite.setTexture(obj->effect.sprite.hurt_right);
      break;
    case WorldObj::DIRECTION_LEFT:
      obj->sprite.setTexture(obj->sprite.death_left);
      obj->sprite.setIdleTexture(obj->sprite.id_left);
      obj->effect.sprite.setTexture(obj->effect.sprite.hurt_left);
      break;
  }
  obj->sprite.lockIntoDeathAnimation();
  obj->effect.sprite.lockAnimation();
  return 0;
}

int RenderHelper::sprite_idle(WorldObj* obj)
{
//if (!obj->sprite.isIdle()) {
  obj->sprite.setTexture((obj->sprite.getIdleTexture()));
  //}
  return 0;
}

int RenderHelper::sprite_update(WorldObj * obj)
{
  return 0;
}

int RenderHelper::sprite_talk(WorldObj * obj)
{
	obj->effect.sprite.unlockAnimation();
	obj->effect.sprite.setTexture(obj->effect.sprite.id_up);

	obj->effect.sprite.setTexture(obj->effect.sprite.talk);

	obj->sprite.lockAnimation();
	obj->effect.sprite.lockAnimation();
	return 0;
}

void RenderHelper::sortVec()
{
  sort(objVec.begin(), objVec.end(), [](WorldObj* a, WorldObj* b) {
    return ((a->body[0].getY() + a->body[0].getHeight()) < (b->body[0].getY() + b->body[0].getHeight()));
  });
}

bool RenderHelper::compY(WorldObj* a, WorldObj* b)
{
  return ((a->getY() + a->getHeight()) < (b->getY() + b->getHeight()));
}

