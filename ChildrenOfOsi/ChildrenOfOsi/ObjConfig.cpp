#include "stdafx.h"
#include "ObjConfig.h"


ObjConfig::ObjConfig()
{
}


ObjConfig::~ObjConfig()
{
}

void ObjConfig::import_config(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{
	Json::Value root;
	Json::Reader reader;


	std::ifstream file("config.json");
	file >> root;

	for (auto itr = root.begin(); itr != root.end(); itr++) 
	{
		set_world_obj(recVec,gameplay_func,tBuffer, (*itr)["x"].asFloat(), (*itr)["y"].asFloat(),
													(*itr)["width"].asFloat(), (*itr)["hight"].asFloat(),
													(*itr)["name"].asString(), (*itr)["tex_file"].asString(), 
													(*itr)["frame_num"].asInt(), 
													(*itr)["bodyx1"].asFloat(), (*itr)["bodyx2"].asFloat(),
													(*itr)["bodyy1"].asFloat(), (*itr)["bodyy2"].asFloat());
	}
	cout << "done" << endl;

}

void ObjConfig::set_world_obj(vector<WorldObj*>* recVec, ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, float x, float y, float width, float hight,
	std::string name, std::string tex_file, int frame_num, float bodyx1, float bodyx2, float bodyy1, float bodyy2)
{
	
	LOG(Containers::texture_table[tex_file]);
	if (Containers::texture_table[tex_file]) {
		cout << tex_file << "Already in Table /////////////////////////////"  << endl;	
	}
	else
	{
		cout << tex_file << "Not in Table /////////////////////////////" << endl;
		gameplay_func->add_texture(tex_file, 0, 0, 0);

		//set file takes up memory
		tBuffer->run();
		Containers::texture_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);
		
	}
	
	gameplay_func->add_worldObj(name, 100*x, 100*y, true);

	tBuffer->run();
	
	Containers::worldObj_table[name]->setWidth(width);
	Containers::worldObj_table[name]->setHeight(hight);
	
	Containers::worldObj_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);
	Containers::worldObj_table[name]->setInteractable(false);

	Containers::worldObj_table[name]->offsetBody(0, 1000, 1000, 1000, 1000);
	
	recVec->push_back(Containers::worldObj_table[name]);
	

}