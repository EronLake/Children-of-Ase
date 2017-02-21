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
		set_world_obj(recVec,	(*itr)["x"].asFloat(), (*itr)["x"].asFloat(), 
								(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
								(*itr)["name"].asString(), (*itr)["tex_file"].asString(), 
								(*itr)["frame_num"].asInt(), 
								(*itr)["bodyx1"].asInt(), (*itr)["bodyx2"].asInt(), 
								(*itr)["bodyy1"].asInt(), (*itr)["bodyy2"].asInt());
	}

}

void ObjConfig::set_world_obj(vector<WorldObj*>* recVec, float x, float y, float width, float hight,
								std::string name,std::string tex_file,int frame_num,float bodyx1,float bodyx2, float bodyy1, float bodyy2)
{
	Texture* tempTexture = new Texture();
	tempTexture->setFile(tex_file,frame_num);
	std::cout << "this is a test"<< std::endl;

	WorldObj* temp_objs = new WorldObj(Vector2f(100 * x, 100 * y), width, hight);
	temp_objs->sprite.setTexture(tempTexture);
	temp_objs->setInteractable(false);
	temp_objs->setName(name);
	temp_objs->offsetBody(0,bodyx1, bodyx2, bodyy1, bodyy2);
	recVec->push_back(temp_objs);

}