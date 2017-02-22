#include "stdafx.h"
#include "ObjConfig.h"


ObjConfig::ObjConfig()
{
}


ObjConfig::~ObjConfig()
{
}

void ObjConfig::import_config(vector<WorldObj*>* recVec)
{
	Json::Value root;
	Json::Reader reader;


	std::ifstream file("config.json");
	file >> root;

	for (auto itr = root.begin(); itr != root.end(); itr++) 
	{
		set_world_obj(recVec,	(*itr)["x"].asFloat(), (*itr)["y"].asFloat(), 
								(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
								(*itr)["name"].asString(), (*itr)["tex_file"].asString(), 
								(*itr)["frame_num"].asInt());
	}

}

void ObjConfig::set_world_obj(vector<WorldObj*>* recVec, float x, float y, float width, float hight,
								std::string name,std::string tex_file,int frame_num)
{
	Texture* tempTexture = new Texture();
	tempTexture->setFile(tex_file);
	tempTexture->load();
	
	tempTexture->setFrames(frame_num);
	
	std::cout << "x:" << 100* x << std::endl;
	std::cout << "y:" << 100 * y << std::endl;

	WorldObj* temp_objs = new WorldObj(Vector2f(100 * x, 100 * y), width, hight);
	temp_objs->sprite.setTexture(tempTexture);
	temp_objs->setInteractable(false);
	temp_objs->setName(name);
	recVec->push_back(temp_objs);

}