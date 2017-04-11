#include "stdafx.h"
#include "TagConfig.h"
#include "Containers.h"


TagConfig::TagConfig()
{
}


TagConfig::~TagConfig()
{
}

void TagConfig::import_config(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer)
{

	Json::Value root;
	Json::Reader reader;


	std::ifstream file("Tag_config.json");
	file >> root;
	int x = 1;
	std::string tempStr = "Tag_";
	std::string tmpTag = "topic_";
	std::vector<std::string> topicVec;
	for (auto itor = root["Tag"].begin(); itor != root["Tag"].end(); itor++){
		int y = 1;
		std::string tmpStr_1 = tempStr;
		int temp_x = x;
		std::string tmpStr_2 = std::to_string(temp_x);
		std::string tmpStr_3 = tmpStr_1 + tmpStr_2;
		for (auto it = root[tmpStr_3]["topics"].begin(); it != root[tmpStr_3]["topics"].end(); it++)
		{
			std::string tmpTag_1 = tmpTag;
			int temp_y = y;
			std::string tmpTag_2 = std::to_string(temp_y);
			std::string tmpTag_3 = tmpTag_1 + tmpTag_2;
			topicVec.push_back((*it)[tmpTag_3].asString());
			y++;
		}
		
	    set_tag(gameplay_func, tBuffer, (*itor)["name"].asString(), topicVec);
	    x++;
    }
	////std::cout<< "done" << endl;




}

void TagConfig::set_tag(ChildrenOfOsi* gameplay_func, TaskBuffer* tBuffer, std::string name, std::vector<std::string> topicVec)
{


		gameplay_func->add_tag(topicVec, name);

		//set file takes up memory
		tBuffer->run();
		//Containers::texture_table[tex_file]->setFile("Assets/Sprites/" + tex_file + ".png", frame_num);
	/* For Spencer
	if (tex_file == "){
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);
	}
	*/

	//gameplay_func->add_worldObj(name, 100 * x, 100 * y, true);

	//tBuffer->run();

	//Containers::worldObj_table[name]->setWidth(width);
	//Containers::worldObj_table[name]->setHeight(hight);

	//Containers::worldObj_table[name]->sprite.setTexture(Containers::texture_table[tex_file]);
	//Containers::worldObj_table[name]->setInteractable(false);

	//Containers::worldObj_table[name]->offsetBody(0, 0, 0, 0, 0);

	//recVec->push_back(Containers::worldObj_table[name]);


}